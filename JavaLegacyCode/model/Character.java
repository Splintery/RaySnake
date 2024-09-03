package model;

import controller.Controller;
import constant.Constant;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

public class Character {

	private Point pos;
	private List<Ray> rays;
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

	
	public void setPos(Point newPos) {pos = newPos;}
	public void setPos(double x, double y) {pos = new Point(x, y);}
	public Point getPos() {return pos;}
	public List<Ray> getRays() {return rays;}


	// private void createRays() {
	// 	for (int i = 0; i < 360; i += 10) {
	// 		rays.add(new Ray(this.pos, pointFromAngle(i)));
	// 	}
	// }
	// public void update() {
	// 	move();
	// 	for (Ray ray : rays) {
	// 		ray.setPos(pos);
	// 	}
	// 	castRays(controller.getBounds());
	// }
	// public void castRays(List<Boundary> bounds) {
	// 	for (Ray ray : rays) {
	// 		ray.updateIntersection(bounds);
	// 	}
	// }


	public void betterUpdate() {
		// move();
		rays = accurateRays(controller.getBounds());
	}

	public List<Ray> accurateRays(List<Boundary> bounds) {
		ArrayList<Ray> res = new ArrayList<Ray>();
		for (Boundary bound : bounds) {
			
			Point start = new Point(bound.getStart());
			Point end = new Point(bound.getEnd());

			double distance = start.getLength(end);
			double ratioT = 10 / distance;
			Point nearStart = new Point((1 - ratioT) * start.getX() + ratioT * end.getX(), (1 - ratioT) * start.getY() + ratioT * end.getY());
			Point nearEnd = new Point((1 - ratioT) * end.getX() + ratioT * start.getX(), (1 - ratioT) * end.getY() + ratioT * start.getY());
			res.add(new Ray(pos, nearStart, bound));
			res.add(new Ray(pos, nearEnd, bound));
			res.add(new Ray(pos, start, bound));
			res.add(new Ray(pos, end, bound));

		}
		Ray.updateDirection(res, bounds);

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