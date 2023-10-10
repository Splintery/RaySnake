package input;

import controller.Controller;

import java.awt.event.MouseMotionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import model.Point;
import constant.Constant;
import shed.Tools;
import model.Ray;

public class MouseInputs implements MouseMotionListener, MouseListener {

	private Controller controller;

	public MouseInputs(Controller controller) {
		this.controller = controller;
	}

	public void mouseMoved(MouseEvent e) {
		// controller.getCharacter().setPos(e.getPoint().getX(), e.getPoint().getY());
	}
	public void mouseDragged(MouseEvent e) {
		controller.move = true;
	}
	public void mouseClicked(MouseEvent e) {
		Point p = new Point(e.getPoint().getX(), e.getPoint().getY());
		controller.getCharacter().setPos(Constant.convertToModel(p));
	}
	public void mouseExited(MouseEvent e) {}
	public void mouseEntered(MouseEvent e) {}
	public void mouseReleased(MouseEvent e) {}
	public void mousePressed(MouseEvent e) {}
}