import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Main {

    public static final String FILENAME = "jobshop1.txt";
    public static final String INSTANCE = "instance ft06";
    public static final int DESIRED_MAKESPAN = 55;

    public static void main(String[] args) {
        int jobs = 0;
        ArrayList<ArrayList<Integer>> order = new ArrayList<>();
        ArrayList<ArrayList<Integer>> jobsTime = new ArrayList<>();
        try {
            File file = new File(FILENAME);
            Scanner reader = new Scanner(file);
            while (reader.hasNextLine()) {
                String data = reader.nextLine();
                if (data.contains(INSTANCE)) {
                    String garbage = reader.nextLine();
                    garbage = reader.nextLine();
                    garbage = reader.nextLine();

                    data = reader.nextLine().trim();
                    String[] jobsAndMachines = data.split(" ");
                    jobs = Integer.parseInt(jobsAndMachines[0]);
                    for (int i = 0; i < jobs; i++) {
                        data = reader.nextLine().trim().replaceAll("  ", ",").replaceAll(" ", ",");
                        String[] splittedData = data.split(",");
                        ArrayList<Integer> machines = new ArrayList<>();
                        ArrayList<Integer> times = new ArrayList<>();
                        for (int j = 0; j < splittedData.length; j++) {
                            if (j % 2 == 0) {
                                machines.add(Integer.parseInt(splittedData[j]));
                            } else {
                                times.add(Integer.parseInt(splittedData[j]));
                            }
                        }
                        order.add(machines);
                        jobsTime.add(times);
                    }

                    break;
                }

            }
            reader.close();
        } catch (FileNotFoundException e) {
            System.out.println("File not exists.");
            e.printStackTrace();
        }

        // TESTS
        if (1 == 0) {
            ArrayList<Integer> maxIterValues = new ArrayList<>(Arrays.asList(10, 20, 30, 40, 50));
            ArrayList<Integer> makespans = new ArrayList<>();

            int min;
            double avg, stdev;

            System.out.println("Testando valores para iteração");
            for (int value : maxIterValues) {
                for (int i = 0; i < 30; i++) {
                    Aco aco = new Aco(jobs, order, jobsTime, 50,
                            value, 1, 1, 0.25, 0.001, DESIRED_MAKESPAN);
                    Pair<ArrayList<Pair<Integer, Integer>>, Integer> result = aco.run();
                    makespans.add(result.getSecond());
                }

                min = makespans.stream().mapToInt(m -> m).min().getAsInt();
                avg =  makespans.stream().mapToInt(m -> m).sum() / 30.0;
                double finalAvg = avg;
                stdev = Math.sqrt(makespans.stream().mapToDouble(m -> ((m - finalAvg) * (m - finalAvg))).sum() / 29.0);

                System.out.println(min);
                System.out.println(avg);
                System.out.println(stdev);

                makespans.clear();
            }

            ArrayList<Integer> antValues = new ArrayList<>(Arrays.asList(25, 50, 75, 100, 200));

            System.out.println("Testando valores para numero de formigas");
            for (int value : antValues) {
                for (int i = 0; i < 30; i++) {
                    Aco aco = new Aco(jobs, order, jobsTime, value,
                            30, 1, 1, 0.25, 0.001, DESIRED_MAKESPAN);
                    Pair<ArrayList<Pair<Integer, Integer>>, Integer> result = aco.run();
                    makespans.add(result.getSecond());
                }

                min = makespans.stream().mapToInt(m -> m).min().getAsInt();
                avg =  makespans.stream().mapToInt(m -> m).sum() / 30.0;
                double finalAvg = avg;
                stdev = Math.sqrt(makespans.stream().mapToDouble(m -> ((m - finalAvg) * (m - finalAvg))).sum() / 29.0);

                System.out.println(min);
                System.out.println(avg);
                System.out.println(stdev);

                makespans.clear();
            }

            ArrayList<Double> pheromoneValues = new ArrayList<>(Arrays.asList(0.0001, 0.001, 0.1, 1.0, 10.0));

            System.out.println("Testando valores para feromonios");
            for (double value : pheromoneValues) {
                for (int i = 0; i < 30; i++) {
                    Aco aco = new Aco(jobs, order, jobsTime, 50,
                            30, 1, 1, 0.25, value, DESIRED_MAKESPAN);
                    Pair<ArrayList<Pair<Integer, Integer>>, Integer> result = aco.run();
                    makespans.add(result.getSecond());
                }

                min = makespans.stream().mapToInt(m -> m).min().getAsInt();
                avg =  makespans.stream().mapToInt(m -> m).sum() / 30.0;
                double finalAvg = avg;
                stdev = Math.sqrt(makespans.stream().mapToDouble(m -> ((m - finalAvg) * (m - finalAvg))).sum() / 29.0);

                System.out.println(min);
                System.out.println(avg);
                System.out.println(stdev);

                makespans.clear();
            }

            ArrayList<Double> alphaValues = new ArrayList<>(Arrays.asList(0.0, 0.5, 1.0, 2.0, 5.0));

            System.out.println("Testando valores para alpha");
            for (double value : alphaValues) {
                for (int i = 0; i < 30; i++) {
                    Aco aco = new Aco(jobs, order, jobsTime, 50,
                            30, value, 1, 0.25, 0.001, DESIRED_MAKESPAN);
                    Pair<ArrayList<Pair<Integer, Integer>>, Integer> result = aco.run();
                    makespans.add(result.getSecond());
                }
                min = makespans.stream().mapToInt(m -> m).min().getAsInt();
                avg =  makespans.stream().mapToInt(m -> m).sum() / 30.0;
                double finalAvg = avg;
                stdev = Math.sqrt(makespans.stream().mapToDouble(m -> ((m - finalAvg) * (m - finalAvg))).sum() / 29.0);

                System.out.println(min);
                System.out.println(avg);
                System.out.println(stdev);

                makespans.clear();
            }

            ArrayList<Double> betaValues = new ArrayList<>(Arrays.asList(0.0, 0.5, 1.0, 2.0, 5.0));

            System.out.println("Testando valores para beta");
            for (double value : betaValues) {
                for (int i = 0; i < 30; i++) {
                    Aco aco = new Aco(jobs, order, jobsTime, 50,
                            30, 1, value, 0.25, 0.001, DESIRED_MAKESPAN);
                    Pair<ArrayList<Pair<Integer, Integer>>, Integer> result = aco.run();
                    makespans.add(result.getSecond());
                }

                min = makespans.stream().mapToInt(m -> m).min().getAsInt();
                avg =  makespans.stream().mapToInt(m -> m).sum() / 30.0;
                double finalAvg = avg;
                stdev = Math.sqrt(makespans.stream().mapToDouble(m -> ((m - finalAvg) * (m - finalAvg))).sum() / 29.0);

                System.out.println(min);
                System.out.println(avg);
                System.out.println(stdev);

                makespans.clear();

            }

            ArrayList<Double> evapValues = new ArrayList<>(Arrays.asList(0.1, 0.25, 0.5, 0.7, 0.9));

            System.out.println("Testando valores para evaporaçao");
            for (double value : evapValues) {
                for (int i = 0; i < 30; i++) {
                    Aco aco = new Aco(jobs, order, jobsTime, 50,
                            30, 1, 1, value, 0.001, DESIRED_MAKESPAN);
                    Pair<ArrayList<Pair<Integer, Integer>>, Integer> result = aco.run();
                    makespans.add(result.getSecond());
                }

                min = makespans.stream().mapToInt(m -> m).min().getAsInt();
                avg =  makespans.stream().mapToInt(m -> m).sum() / 30.0;
                double finalAvg = avg;
                stdev = Math.sqrt(makespans.stream().mapToDouble(m -> ((m - finalAvg) * (m - finalAvg))).sum() / 29.0);

                System.out.println(min);
                System.out.println(avg);
                System.out.println(stdev);

                makespans.clear();
            }

        }


        // Final
        if (1 == 1) {
            ArrayList<Integer> makespans = new ArrayList<>();

            System.out.println("Resultados finais");
            for (int i = 0; i < 30; i++) {
                Aco aco = new Aco(jobs, order, jobsTime, 200,
                        30, 0, 5, 0.5, 10, DESIRED_MAKESPAN);
                Pair<ArrayList<Pair<Integer, Integer>>, Integer> result = aco.run();
                makespans.add(result.getSecond());
            }

            int min = makespans.stream().mapToInt(m -> m).min().getAsInt();
            double avg =  makespans.stream().mapToInt(m -> m).sum() / 30.0;
            double finalAvg = avg;
            double stdev = Math.sqrt(makespans.stream().mapToDouble(m -> ((m - finalAvg) * (m - finalAvg))).sum() / 29.0);

            System.out.println(min);
            System.out.println(avg);
            System.out.println(stdev);

            makespans.clear();
        }

    }
}
