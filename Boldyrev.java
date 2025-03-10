package brokenrobotgame.model;

import brokenrobotgame.model.events.RobotActionEvent;
import brokenrobotgame.model.events.RobotActionListener;
import brokenrobotgame.model.factory.RobotFactory;
import brokenrobotgame.model.navigation.CellPosition;
import brokenrobotgame.model.navigation.Direction;
import brokenrobotgame.model.navigation.MiddlePosition;
import brokenrobotgame.model.robots.*;

public class GameModel
{
    private static int startRobotsAmountOfCharge = 12;
    private static int startRobotsChargeCapacity = 20;


    GameField _field = new GameField();
    public GameField field(){
        return _field;
    }

    // ----------------------------------------------

    private AbstractRobot _robot;


    public AbstractRobot robot(){
        return _field.robot();
    }
    // ----------------------------------------------

    public void start()
    {
        generateField();

        identifyGameOver();

        _field.robot().addRobotActionListener(new RobotObserver());
    }
    
    // ----------------------------------------------
    CellPosition _targetPos;
    
    public CellPosition targetPosition(){
        return _targetPos;
    }
    
    // ------------------------

    private void generateField()
    {

        _robot = RobotFactory.createRandomRobot(_field);

        _robot.useBattery(new Battery(_field, startRobotsChargeCapacity, startRobotsAmountOfCharge));
        _field.setRobot(new CellPosition(3, 3), _robot);

        _field.addWall(new MiddlePosition(robot().position(), Direction.east()), new WallPiece(_field));
        _field.addWall(new MiddlePosition(robot().position(), Direction.south()), new WallPiece(_field));
        Battery outBattery = new Battery(_field, 5, 3);

        _field.addBattery(new CellPosition(4, 4), outBattery);
        _field.addBattery(robot().position().next(Direction.south()).next(Direction.south()), outBattery);

        _field.addDoor(new MiddlePosition(new CellPosition(5, 4), Direction.east()), new Door(_field));
        _field.addDoor(new MiddlePosition(new CellPosition(1, 1), Direction.north()), new Door(_field));

        _targetPos = robot().position().next(Direction.west());
    }

    private void destroyAllBatteries()
    {
        _field.clearAllBatteries();
    }
    
    private void identifyGameOver(){
        
        if(robot().position().equals(_targetPos))
        {
            System.out.println("You reach target position!!!");
            destroyAllBatteries();
        }
        else if(robot().amountOfCharge() == 0)
        {
            System.out.println("You amount of charge is null!!!");
        }
    }   
    
    private class RobotObserver implements RobotActionListener
    {
        @Override
        public void robotMadeMove(RobotActionEvent e) {
            identifyGameOver();
        }
    }
}
