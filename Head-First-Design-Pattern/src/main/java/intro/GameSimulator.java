package intro;

import intro.duck.MallardDuck;
import intro.duck.ToyDuck;

/**
 * 游戏模拟器
 */
public class GameSimulator {
    public static void main(String[] args) {
        Duck mallard = new MallardDuck();
        mallard.performFly();
        mallard.performQuack();

        System.out.println("-------------");

        Duck toy = new ToyDuck();
        toy.performFly();
        toy.performQuack();
    }
}
