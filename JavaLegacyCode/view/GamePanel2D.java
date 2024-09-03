package view;

import controller.Controller;

import model.Character;
import model.Ray;
import model.Boundary;
import model.Point;
import constant.Constant;
import shed.Tools;

import javax.swing.JPanel;
import java.awt.Graphics;
import java.awt.Color;
import java.util.LinkedList;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

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

		Polygon fov = new Polygon();
		List<Point> tmp = Ray.getConvertedListOfPointsFromRays(controller.getCharacter().getRays());
		List<Point> pol = getPolygon(controller.getCharacter(), tmp);
		for (Point p : pol) {
			fov.addPoint((int) p.getX(), (int) p.getY());
		}
		g.fillPolygon(fov);

		drawAllBoundarys(controller.getBounds(), g);

		drawAllRays(controller.getCharacter().getRays(), g);

		drawCharacter(controller.getCharacter(), g);

	}

	public static double calculateAngle(Point p0, Point p) {
        double x = p.getX() - p0.getX();
        double y = p.getY() - p0.getY();
        double angle = Math.toDegrees(Math.atan2(y, x));
        if (angle < 0) {
        	angle += 360;
        }
        return angle;
    }
    public static List<Point> getPolygon(Character c, List<Point> points) {
    	Point center = Constant.convertToPixels(c.getPos());
    	ArrayList<Point> polygon = new ArrayList<Point>();

    	for (Point p1 : points) {
    		int index = 0;
    		double angle1 = calculateAngle(center, p1);
    		for (Point p2 : polygon) {
    			double angle2 = calculateAngle(center, p2);

    			if (angle1 < angle2) {
    				break;
    			} else if (angle1 > angle2) {
    				index++;
    			} else {
    				double distance1 = Math.hypot(center.getX() - p1.getX(), center.getY() - p1.getY());
    				double distance2 = Math.hypot(center.getX() - p2.getX(), center.getY() - p2.getY());
    				if (distance1 < distance2) {
    					break;
    				} else {
    					index++;
    				}
    			}
    		}
    		polygon.add(index, p1);
    	}
    	return polygon;
    }


	private static void drawAllRays(List<Ray> rays, Graphics g) {
		g.setColor(Color.RED);
		for (Ray ray : rays) {
			drawRay(ray, g);
		}
		g.setColor(Color.GREEN);
	}
	private static void drawRay(Ray ray, Graphics g) {
		Point pos = Constant.convertToPixels(ray.getPos());
		Point dir = Constant.convertToPixels(ray.getDir());
		drawLine(pos, dir, g);
	}
	private static void drawAllBoundarys(List<Boundary> bounds, Graphics g) {
		g.setColor(Color.WHITE);
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
	private static void drawLine(Point a, Point b, Graphics g) {
		g.drawLine((int) a.getX(), (int) a.getY(), (int) b.getX(), (int) b.getY());
	}
}