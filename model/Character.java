package model;

import controller.Controller;

import java.util.LinkedList;
import java.util.concurrent.ThreadLocalRandom;

public class Character {

	private Point pos;
	private LinkedList<Ray> rays;
	private Controller controller;

	private Point target;

	public Character(Controller controller, Point pos) {
		this.target = new Point(1440, 960);

		this.pos = pos;
		this.controller = controller;
		rays = new LinkedList<Ray>();
		createRays();
	}
	public Character(Controller controller, int x, int y) {
		this(controller, new Point(x, y));
	}

	private void createRays() {
		for (int i = 0; i < 360; i += 1) {
			rays.add(new Ray(this.pos, pointFromAngle(i)));
		}
	}
	private void createRaysSmart(LinkedList<Boundary> bounds) {
		for (Boundary bound : bounds) {
			rays.add(new Ray(this.pos, bound.getStart()));
			rays.add(new Ray(this.pos, bound.getEnd()));
		}
	}
	private Point pointFromAngle(int i) {
		double x = Math.cos(Math.toRadians(i));
		double y = Math.sin(Math.toRadians(i));
		return new Point(x, y);
	}

	public void setPos(Point newPos) {pos = newPos;}
	public void setPos(double x, double y) {
		// clearIntersections();
		pos = new Point(x, y);

		castRays(controller.getBoundarys());
	}
	public Point getPos() {return pos;}
	public LinkedList<Ray> getRays() {return rays;}

	public void update() {
		for (Ray ray : rays) {
			ray.setPos(pos);
		}
	}

	public void castRays(LinkedList<Boundary> bounds) {
		for (Ray ray : rays) {
			ray.updateIntersection(bounds);
		}
	}
	public void castRaysSmart(LinkedList<Boundary> bounds) {
		rays.clear();
		createRaysSmart(bounds);
		for (Ray ray : rays) {
			ray.updateIntersection(bounds);
		}
	}

	public void clearIntersections() {
		for (Ray ray : rays) {
			ray.resetIntersection();
		}
	}

	public void setTarget() {
		int width = 1440;
		int height = 960;

		double randomX = ThreadLocalRandom.current().nextInt(0, width + 1);
		double randomY = ThreadLocalRandom.current().nextInt(0, height + 1);

		target = new Point(randomX, randomY);
	}
	public void move() {
		double newX = target.getX() - this.pos.getX();
		double newY = target.getY() - this.pos.getY();
		setPos(this.pos.getX() + 0.001 * newX, this.pos.getY() + 0.001 * newY);
	}
}