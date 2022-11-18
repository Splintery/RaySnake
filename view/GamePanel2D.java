package view;

import controller.Controller;

import model.Character;
import model.Ray;
import model.Boundary;
import model.Point;
import constant.Constant;

import javax.swing.JPanel;
import java.awt.Graphics;
import java.awt.Color;
import java.util.LinkedList;

import java.awt.Polygon;

public class GamePanel2D extends JPanel {

	private Controller controller;

	public GamePanel2D(Controller controller) {
		this.controller = controller;
		setBackground(Color.BLACK);
	}

	@Override
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.setColor(Color.GREEN);

		drawAllBoundarys(controller.getBounds(), g);
		// drawAllIntersections(controller.getCharacter(), g);
		// testRender(controller.getCharacter(), g);
		drawAllRays(controller.getCharacter().getRays(), g);
		drawCharacter(controller.getCharacter(), g);


	}

	// private static void testRender(Character character, Graphics g) {
	// 	Polygon visiblePlane = new Polygon();
	// 	for (Ray ray : character.getRays()) {
	// 		if (ray.getIntersection() != null) {
	// 			visiblePlane.addPoint((int) ray.getIntersection().getX(), (int) ray.getIntersection().getY());
	// 		}
	// 	}
	// 	g.fillPolygon(visiblePlane);
	// }
	private static void drawAllRays(LinkedList<Ray> rays, Graphics g) {
		for (Ray ray : rays) {
			drawRay(ray, g);
		}
	}
	private static void drawRay(Ray ray, Graphics g) {
		Point pos = Constant.convertToPixels(ray.getPos());
		Point dir = Constant.convertToPixels(ray.getDir());
		drawLine(pos, dir, g);
	}
	private static void drawAllBoundarys(LinkedList<Boundary> bounds, Graphics g) {
		g.setColor(Color.RED);
		for (Boundary bound : bounds) {
			drawBoundary(bound, g);
		}
		g.setColor(Color.GREEN);
	}
	private static void drawBoundary(Boundary bound, Graphics g) {
		Point start = Constant.convertToPixels(bound.getStart());
		Point end = Constant.convertToPixels(bound.getEnd());
		
		drawLine(start, end, g);
	}

	private static void drawAllIntersections(Character character, Graphics g) {
		for (Ray ray : character.getRays()) {
			drawIntersection(ray, g);
		}
	}
	private static void drawLine(Point a, Point b, Graphics g) {
		g.drawLine((int) a.getX(), (int) a.getY(), (int) b.getX(), (int) b.getY());
	}
	private static void drawIntersection(Ray ray, Graphics g) {
		Point it = ray.getIntersection();
		Point pos = Constant.convertToPixels(ray.getPos());
		if (it != null) {
			it = Constant.convertToPixels(it);
			drawLine(it, pos, g);
		}
	}
	private void drawCharacter(Character character, Graphics g) {
		g.setColor(Color.RED);
		Point pos = Constant.convertToPixels(character.getPos());
		g.fillOval((int) pos.getX() - 5, (int) pos.getY() - 5, 10, 10);
		g.setColor(Color.GREEN);
	}
}