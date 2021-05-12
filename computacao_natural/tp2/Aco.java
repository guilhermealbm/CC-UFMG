import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Aco {

    private static final Pair<Integer, Integer> firstPair = new Pair<>(-1, -1);
    private static final Pair<Integer, Integer> lastPair = new Pair<>(-10, -10);

    private int jobs;
    private ArrayList<ArrayList<Integer>> order;
    private ArrayList<ArrayList<Integer>> jobsTime;
    private int ants;
    private int maxIter;
    private double alpha;
    private double beta;
    private double evaporation;
    private double pheromone;
    private int desiredMakespan;

    // ArrayList<Pair<Integer, Integer>> == List of nodes
    private HashMap<Pair<Integer, Integer>, ArrayList<Pair<Integer, Integer>>> stdGraph;
    private HashMap<Pair<Integer, Integer>, ArrayList<Pair<Integer, Integer>>> jsspGraph;

    private ArrayList<Pair<Integer, Integer>> tasks;
    HashMap<Pair<Integer, Integer>, Integer> taskTimes;
    HashMap<Pair<Integer, Integer>, Integer> desirability;
    HashMap<Pheromone, Double> pheromones;

    public Aco(int jobs, ArrayList<ArrayList<Integer>> order, ArrayList<ArrayList<Integer>> jobsTime, int ants,
               int maxIter, double alpha, double beta, double evaporation, double pheromone, int desiredMakespan) {
        this.jobs = jobs;
        this.order = order;
        this.jobsTime = jobsTime;
        this.ants = ants;
        this.maxIter = maxIter;
        this.alpha = alpha;
        this.beta = beta;
        this.evaporation = evaporation;
        this.pheromone = pheromone;
        this.desiredMakespan = desiredMakespan;

        // Creating graphs
        this.stdGraph = new HashMap<>();
        this.jsspGraph = new HashMap<>();

        this.tasks = new ArrayList<>();
        this.taskTimes = new HashMap<>();
        this.desirability = new HashMap<>();
        this.pheromones = new HashMap<>();
    }

    // Returns path and min makespan
    public Pair<ArrayList<Pair<Integer, Integer>>, Integer> run() {

        // Init graph and storing tasks
        for (int i = 0; i < this.jobs; i++) {
            for (int j = 0; j < this.order.get(i).size(); j++) {
                Pair<Integer, Integer> newTask = new Pair<>(i, this.order.get(i).get(j));
                this.stdGraph.put(newTask, new ArrayList<>());
                this.tasks.add(newTask);
            }
        }

        // Add edges between pairs
        for (Pair<Integer, Integer> task : this.tasks) {
            for (Pair<Integer, Integer> task2 : this.tasks) {
                if (task != task2)
                    this.stdGraph.get(task).add(task2);
            }
        }

        this.stdGraph.put(firstPair, new ArrayList<>());

        // Full connect
        for (int i = 0; i < this.jobs; i++)
            this.stdGraph.get(firstPair).add(new Pair<>(i, this.order.get(i).get(0)));

        // Create jssp graph
        getJsspGraph();

        getTimesSpent();
        getDesirability();
        pheromonesInitializer();

        ArrayList<Pair<Integer, Integer>> bestPath = null;
        int bestMakespan = 999999998;

        for (int i = 0; i < maxIter; i++) {

            ArrayList<ArrayList<Pair<Integer, Integer>>> paths = new ArrayList<>();
            ArrayList<Integer> makespans = new ArrayList<>();

            for (int j = 0; j < ants; j++) {
                ArrayList<Pair<Integer, Integer>> path = generatePath();
                paths.add(path);

                int makespan = calcMakespan(path);
                makespans.add(makespan);

                // ifs just for feedback
                if (bestPath == null || makespan < bestMakespan) {
                    bestPath = path;
                    bestMakespan = makespan;
                }

                if (bestMakespan == this.desiredMakespan) {
                    System.out.println("Makespan ótimo encontrado. Iteração " + i);
                    this.desiredMakespan = 999999999;
                }

                //end of if just for feedback

            }

            updatePheromones(paths, makespans);
        }

        return new Pair<>(bestPath, bestMakespan);
    }

    // Returns jssp graph
    private void getJsspGraph() {

        this.jsspGraph.put(firstPair, new ArrayList<>());
        this.jsspGraph.put(lastPair, new ArrayList<>());

        // Init graph
        for (Pair<Integer, Integer> task : this.tasks)
            this.jsspGraph.put(task, new ArrayList<>());

        // Connecting first node to firsts tasks
        for (int i = 0; i < this.jobs; i++) {
            int first = this.order.get(i).get(0);
            this.jsspGraph.get(firstPair).add(new Pair<>(i, first));
        }

        // Connect same job tasks
        for (Pair<Integer, Integer> task : this.tasks) {
            int index = this.order.get(task.getFirst()).indexOf(task.getSecond());
            if (index > this.order.get(task.getFirst()).size() - 2)
                this.jsspGraph.get(task).add(lastPair);
            else
                this.jsspGraph.get(task).add(new Pair<>(task.getFirst(),
                        this.order.get(task.getFirst()).get(index + 1)));
        }

        // Connect same machines tasks
        for (Pair<Integer, Integer> task : this.tasks) {
            for (Pair<Integer, Integer> task2 : this.tasks) {
                if (!task.equals(task2)) {
                    if (task.getSecond().equals(task2.getSecond()))
                        this.jsspGraph.get(task).add(task2);

                }
            }
        }

    }

    private void getTimesSpent() {

        for (int i = 0; i < this.jobs; i++) {
            for (int j = 0; j < this.order.get(i).size(); j++) {
                Pair<Integer, Integer> task = new Pair<>(i, this.order.get(i).get(j));
                this.taskTimes.put(task, this.jobsTime.get(i).get(j));
            }
        }

        this.taskTimes.put(lastPair, 0);

    }

    private void getDesirability() {

        for (int i = 0; i < this.jobs; i++) {
            ArrayList<Integer> taskOrder = this.order.get(i);

            for (int j = 0; j < taskOrder.size(); j++) {
                int finalJ = j;
                int sum = this.jobsTime.get(i).stream().mapToInt(n -> n).filter((n) -> n >= finalJ).sum();
                Pair<Integer, Integer> key = new Pair<>(i, taskOrder.get(j));
                this.desirability.put(key, sum);
            }
        }
    }

    private void pheromonesInitializer() {

        for (int i = 0; i < this.jobs; i++) {
            int finalI = i;
            // Recovery already existing pair
            Pair<Integer, Integer> desiredPair = this.tasks.stream()
                    .filter(pair -> pair.getFirst().equals(finalI)
                            && pair.getSecond().equals(this.order.get(finalI).get(0)))
                    .findFirst().get();
            Pheromone pheromone_ = new Pheromone(firstPair, desiredPair);
            this.pheromones.put(pheromone_, this.pheromone);
        }

        for (Pair<Integer, Integer> task : this.tasks) {
            for (Pair<Integer, Integer> task2 : this.tasks) {
                if (!task.equals(task2)) {
                    Pheromone pheromone_ = new Pheromone(task, task2);
                    this.pheromones.put(pheromone_, this.pheromone);
                }
            }
        }

    }

    private ArrayList<Pair<Integer, Integer>> generatePath() {

        // Copy objects to prevent modifications
        ArrayList<Pair<Integer, Integer>> tasksCopy = new ArrayList<>();
        for (Pair<Integer, Integer> task : this.tasks)
            tasksCopy.add(new Pair<>(task.getFirst(), task.getSecond()));

        ArrayList<Pair<Integer, Integer>> initialNodes = new ArrayList<>();
        for (Pair<Integer, Integer> node : this.jsspGraph.get(firstPair))
            initialNodes.add(new Pair<>(node.getFirst(), node.getSecond()));

        ArrayList<Pair<Integer, Integer>> path = new ArrayList<>();
        Pair<Integer, Integer> lastVisited = firstPair;

        while (tasksCopy.size() != 0) {
            ArrayList<Double> newPheromones = new ArrayList<>();
            ArrayList<Integer> newDesirability = new ArrayList<>();

            // get all eligible nodes pheromone and desirability
            for (Pair<Integer, Integer> task : initialNodes) {
                Pair<Integer, Integer> finalLastVisited1 = lastVisited;
                double value = this.pheromones.entrySet().stream().
                        filter(p -> p.getKey().getPair1().equals(finalLastVisited1)
                                && p.getKey().getPair2().equals(task)).
                        findFirst().get().getValue();
                newPheromones.add(value);

                newDesirability.add(this.desirability.entrySet().stream().
                        filter(p -> p.getKey().equals(task)).
                        findFirst().get().getValue());
            }

            ArrayList<Double> probs = new ArrayList<>();

            for (int i = 0; i < initialNodes.size(); i++) {
                double value = Math.pow(newPheromones.get(i), this.alpha) * Math.pow(newDesirability.get(i), this.beta);
                probs.add(value);
            }

            double sum = probs.stream().mapToDouble(v -> v).sum();

            // Weighted randomness
            int idx = 0;
            for (double r = Math.random() * sum; idx < initialNodes.size() - 1; ++idx) {
                r -= probs.get(idx);
                if (r <= 0.0) break;
            }

            lastVisited = initialNodes.get(idx);

            initialNodes.remove(lastVisited);
            Pair<Integer, Integer> finalLastVisited2 = lastVisited;
            // filter is need because its a copied object
            tasksCopy.remove(tasksCopy.stream().
                    filter(p -> p.equals(finalLastVisited2)).
                    findFirst().get());
            tasksCopy.remove(lastVisited);
            path.add(lastVisited);

            // check next machine from job
            int index = this.order.get(lastVisited.getFirst()).indexOf(lastVisited.getSecond());
            if (index <= this.order.get(lastVisited.getFirst()).size() - 2) {
                Pair<Integer, Integer> finalLastVisited = lastVisited;
                Pair<Integer, Integer> pair = this.tasks.stream().
                        filter(p -> p.getFirst().equals(finalLastVisited.getFirst())
                                && p.getSecond().equals(this.order.get(finalLastVisited.getFirst()).get(index + 1))).
                        findFirst().get();
                initialNodes.add(pair);
            }

        }

        return path;

    }

    private int calcMakespan(ArrayList<Pair<Integer, Integer>> path) {

        HashMap<Pair<Integer, Integer>, ArrayList<Pair<Integer, Integer>>> graph = new HashMap<>();
        graph = copy(this.jsspGraph);

        for (Pair<Integer, Integer> task_ : this.tasks) {

            ArrayList<Pair<Integer, Integer>> edges = graph.get(task_);
            Pair<Integer, Integer> task = path.stream().filter(p -> p.equals(task_)).findFirst().get();

            ArrayList<Pair<Integer, Integer>> toRemove = new ArrayList<>();
            for (Pair<Integer, Integer> edge : edges) {
                if ((!edge.equals(lastPair)) && edge.getSecond().equals(task.getSecond())) {
                    Pair<Integer, Integer> edge_ = path.stream().filter(p -> p.equals(edge)).findFirst().get();
                    if (path.indexOf(task) > path.indexOf(edge_)) {
                        Pair<Integer, Integer> pairToRemove = graph.entrySet().stream().
                                filter(p -> p.getKey().equals(edge_)).findFirst().get().getKey();
                        toRemove.add(pairToRemove);
                    }

                }
            }
            graph.get(task_).removeAll(toRemove);
        }

        HashMap<Pair<Integer, Integer>, Integer> times = new HashMap<>();
        //Initializing times
        for (Pair<Integer, Integer> task : path)
            times.put(task, -1);

        times.put(firstPair, 0);
        times.put(lastPair, -1);

        // filter is need because its a copied object
        for (Pair<Integer, Integer> edge_ : graph.get(firstPair)) {
            int time = this.taskTimes.entrySet().stream().
                    filter(p -> p.getKey().equals(edge_)).findFirst().get().getValue();
            Pair<Integer, Integer> edge = times.entrySet().stream().
                    filter(p -> p.getKey().equals(edge_)).findFirst().get().getKey();
            times.put(edge, time);
        }


        for (Pair<Integer, Integer> task : path) {
            // filter is need because its a copied object
            ArrayList<Pair<Integer, Integer>> edges = graph.entrySet().stream().
                    filter(p -> p.getKey().equals(task)).findFirst().get().getValue();
            for (Pair<Integer, Integer> edge : edges) {

                Map.Entry<Pair<Integer, Integer>, Integer> edgeEntry = times.entrySet().stream().
                        filter(p -> p.getKey().equals(edge)).findFirst().get();

                int taskTime1 = times.entrySet().stream().
                        filter(p -> p.getKey().equals(task)).findFirst().get().getValue();

                int taskTime2 = this.taskTimes.entrySet().stream().
                        filter(p -> p.getKey().equals(edge)).findFirst().get().getValue();

                if (edgeEntry.getValue() < taskTime1 + taskTime2)
                    times.put(edgeEntry.getKey(), taskTime1 + taskTime2);

            }
        }

        return times.get(lastPair);

    }

    private void updatePheromones(ArrayList<ArrayList<Pair<Integer, Integer>>> paths,
                                                        ArrayList<Integer> makespans) {

        this.pheromones.forEach((k, v) -> this.pheromones.put(k, v * (1 - this.evaporation)));

        double Q = 1.0;

        for (int i = 0; i < paths.size(); i++) {
            ArrayList<Pair<Integer, Integer>> path = paths.get(i);
            int makespan = makespans.get(i);

            Map.Entry<Pheromone, Double> pheromone = this.pheromones.entrySet().stream()
                    .filter(p -> p.getKey().getPair1().equals(firstPair)
                            && p.getKey().getPair2().equals(path.get(0)))
                    .findFirst().get();

            this.pheromones.put(pheromone.getKey(), pheromone.getValue() + (Q / makespan));

            for (int j = 0; j < path.size() - 1; j++) {
                int finalJ = j;
                pheromone = this.pheromones.entrySet().stream()
                        .filter(pair -> pair.getKey().getPair1().equals(path.get(finalJ))
                                && pair.getKey().getPair2().equals(path.get(finalJ + 1)))
                        .findFirst().get();
                this.pheromones.put(pheromone.getKey(), pheromone.getValue() + (Q / makespan));

            }

        }

    }

    // deep copy hash map
    public static HashMap<Pair<Integer, Integer>, ArrayList<Pair<Integer, Integer>>> copy(
            HashMap<Pair<Integer, Integer>, ArrayList<Pair<Integer, Integer>>> original) {
        HashMap<Pair<Integer, Integer>, ArrayList<Pair<Integer, Integer>>> copy = new HashMap<>();

        for (Map.Entry<Pair<Integer, Integer>, ArrayList<Pair<Integer, Integer>>> entry : original.entrySet())
            copy.put(entry.getKey(), new ArrayList<>(entry.getValue()));
        return copy;

    }

}
