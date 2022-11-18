package model;

import controller.Controller;
import constant.Constant;

import java.util.LinkedList;
import java.util.concurrent.ThreadLocalRandom;

public class Character {

	private Point pos;
	private LinkedList<Ray> rays;
	private Controller controller;

	private Point target;

	public Character(Controller controller, Point pos) {
		setTarget();

		this.pos = pos;
		this.controller = controller;
		rays = accurateRays(controller.getBounds());
	}
	public Character(Controller controller, double x, double y) {
		this(controller, new Point(x, y));
	}
	public Character(Controller controller) {
		this(controller, new Point(Constant.WIDTH / 2, Constant.HEIGHT / 2));
	}

	

	public static double angleFromPoint(Point point) {
		double angle = 0.0;
		if (point.getX() == 0 && point.getY() == 0) {
			return angle;
		}
		if (point.getX() > 0) {
			if (point.getY() > 0) {
				angle = Math.abs(Math.toDegrees(Math.atan(point.getY() / point.getX())));
			} else {
				angle = 360.0 - Math.abs(Math.toDegrees(Math.atan(point.getY() / point.getX())));
			}
		} else {
			if (point.getY() > 0) {
				angle = 180.0 - Math.abs(Math.toDegrees(Math.atan(point.getY() / point.getX())));
			} else {
				angle = 180.0 + Math.abs(Math.toDegrees(Math.atan(point.getY() / point.getX())));
			}
		}
		
		return angle;
	}

	public static Point pointFromAngle(int i) {
		double x = Math.cos(Math.toRadians(i));
		double y = Math.sin(Math.toRadians(i));
		return new Point(x, y);
	}

	public void setPos(Point newPos) {pos = newPos;}
	public void setPos(double x, double y) {pos = new Point(x, y);}
	public Point getPos() {return pos;}
	public LinkedList<Ray> getRays() {return rays;}


	private void createRays() {
		for (int i = 0; i < 360; i += 10) {
			rays.add(new Ray(this.pos, pointFromAngle(i)));
		}
	}
	public void update() {
		move();
		for (Ray ray : rays) {
			ray.setPos(pos);
		}
		castRays(controller.getBounds());
	}
	public void castRays(LinkedList<Boundary> bounds) {
		for (Ray ray : rays) {
			ray.updateIntersection(bounds);
		}
	}


	public void betterUpdate() {
		move();
		rays = accurateRays(controller.getBounds());
	}

	public LinkedList<Ray> accurateRays(LinkedList<Boundary> bounds) {
		LinkedList<Ray> res = new LinkedList<Ray>();
		for (Boundary bound : bounds) {
			res.add(new Ray(pos, bound.getStart()));
			res.add(new Ray(pos, bound.getEnd()));
		}
		Ray.updateIntersection(res, bounds);

		return res;
	}

	public void setTarget() {
		double randomX = ThreadLocalRandom.current().nextInt((int) Math.ceil(-Constant.WIDTH / 2), (int) Math.floor(Constant.WIDTH / 2) + 1);
		double randomY = ThreadLocalRandom.current().nextInt((int) Math.ceil(-Constant.HEIGHT / 2), (int) Math.floor(Constant.HEIGHT / 2) + 1);

		target = new Point(randomX, randomY);
	}
	public void move() {
		double newX = target.getX() - pos.getX();
		double newY = target.getY() - pos.getY();
		setPos(pos.getX() + 0.001 * newX, pos.getY() + 0.001 * newY);
	}
}