public class Pheromone {

    Pair<Integer, Integer> pair1;
    Pair<Integer, Integer> pair2;

    public Pheromone(Pair<Integer, Integer> pair1, Pair<Integer, Integer> pair2) {
        this.pair1 = pair1;
        this.pair2 = pair2;
    }

    public Pair<Integer, Integer> getPair1() {
        return pair1;
    }

    public void setPair1(Pair<Integer, Integer> pair1) {
        this.pair1 = pair1;
    }

    public Pair<Integer, Integer> getPair2() {
        return pair2;
    }

    public void setPair2(Pair<Integer, Integer> pair2) {
        this.pair2 = pair2;
    }
}