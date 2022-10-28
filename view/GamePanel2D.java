package view;

import controller.Controller;

import model.Character;
import model.Ray;
import model.Boundary;
import model.Point;

import javax.swing.JPanel;
import java.awt.Graphics;
import java.awt.Color;
import java.util.LinkedList;

import java.awt.Polygon;

public class GamePanel2D extends JPanel {

	private Controller controller;
	private static final int BLOCK_SIZE = 16;
	
	public GamePanel2D(Controller controller) {
		this.controller = controller;
		setBackground(Color.BLACK);
	}

	@Override
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.setColor(Color.GREEN);

		drawAllBoundarys(controller.getBoundarys(), g);
		drawAllIntersections(controller.getCharacter(), g);


	}

	private static void testRender(Character character, Graphics g) {
		Polygon visiblePlane = new Polygon();
		for (Ray ray : character.getRays()) {
			if (ray.getIntersection() != null) {
				visiblePlane.addPoint((int) ray.getIntersection().getX(), (int) ray.getIntersection().getY());
			}
		}
		g.fillPolygon(visiblePlane);
	}
	private static void drawRay(Ray ray, Graphics g) {
		int multiplier = 1;
		int posX = (int) ray.getPos().getX();
		int posY = (int) ray.getPos().getY();
		g.drawLine(posX, posY, (int) (ray.getDir().getX() * (BLOCK_SIZE * multiplier)) + posX, (int) (ray.getDir().getY() * (BLOCK_SIZE * multiplier)) + posY);
	}
	private static void drawAllBoundarys(LinkedList<Boundary> bounds, Graphics g) {
		for (Boundary bound : bounds) {
			drawBoundary(bound, g);
		}
	}
	private static void drawBoundary(Boundary bound, Graphics g) {
		int startX = (int) bound.getStart().getX();
		int startY = (int) bound.getStart().getY();
		int endX = (int) bound.getEnd().getX();
		int endY = (int) bound.getEnd().getY();
		g.drawLine(startX, startY, endX, endY);
	}

	private static void drawAllIntersections(Character character, Graphics g) {
		for (Ray ray : character.getRays()) {
			drawIntersection(ray, g);
		}
	}
	private static void drawIntersection(Ray ray, Graphics g) {
		Point it = ray.getIntersection();
		if (it != null) {
			g.drawLine((int) it.getX(), (int) it.getY(), (int) ray.getPos().getX(), (int) ray.getPos().getY());
		}
	}
	private void drawCharacter(Character character, Graphics g) {
		if (character.getRays() != null) {
			for (Ray ray : character.getRays()) {
				drawRay(ray, g);
			}
		} else {
			System.out.println("rays is null");
		}
	}
}