package input;

import controller.Controller;

import java.awt.event.MouseMotionListener;
import java.awt.event.MouseEvent;

public class MouseInputs implements MouseMotionListener {

	private Controller controller;

	public MouseInputs(Controller controller) {
		this.controller = controller;
	}

	public void mouseMoved(MouseEvent e) {
		// controller.getCharacter().setPos(e.getPoint().getX(), e.getPoint().getY());
	}
	public void mouseDragged(MouseEvent e) {}
}