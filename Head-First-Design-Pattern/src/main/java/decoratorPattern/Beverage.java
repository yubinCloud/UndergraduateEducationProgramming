package decoratorPattern;

/**
 * 材料类
 * 所有调料和咖啡都继承自该类
 */
public abstract class Beverage {
    protected String description = "Unknown Beverage";

    public String getDescription() {
        return description;
    }

    public abstract double cost();
}
