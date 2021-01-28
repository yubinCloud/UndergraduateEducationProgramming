package intro.quack;

import intro.QuackBehavior;

/**
 * 吱吱叫
 */
public class Squeak implements QuackBehavior {
    @Override
    public void quack() {
        System.out.println("I'm squeaking.");
    }
}
