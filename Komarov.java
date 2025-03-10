package Model.units;

import Model.updatableunit.UpdatableUnit;

// 
public class Box extends UpdatableUnit {

    // ----------------------------------------------

    private boolean _isOpen = false;
    
    public boolean isOpen() {
        return _isOpen;
    }
    
    public void open(Key key) {
        if( key.belongTo(Robot.class) && key.isNeighbor(this) ) {
            _isOpen = true;

            fireStateChanged();
        }
    }

    // -----------------------------------------------------------------

    @Override
    public String toString() {

        String msg = "Box";

        msg += "(";
        if( isOpen() ) {
            msg += "o";
        } else {
            msg += "cl";
        }
        msg += ")";

        return msg;
    }
}
