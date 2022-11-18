package model;

import java.util.LinkedList;

public class Ray {

	private Point pos;
	private Point dir;

	private Point intersection = null;

	public Ray(Point pos, Point dir) {
		this.pos = pos;
		this.dir = dir;
	}
	public Ray(int x1, int y1, int x2, int y2) {
		pos = new Point(x1, y1);
		dir = new Point(x2, y2);
	}

	public Point getPos() {return pos;}
	public Point getDir() {return dir;}

	public void setPos(Point newPos) {pos = newPos;}

	public void lookAt(Point p) {
		dir = new Point((int) (p.getX() - pos.getX()), (int) (p.getY() - pos.getY()));
	}

	public Point cast(Boundary bound) {
		double x1 = bound.getStart().getX();
		double y1 = bound.getStart().getY();
		double x2 = bound.getEnd().getX();
		double y2 = bound.getEnd().getY();

		double x3 = pos.getX();
		double y3 = pos.getY();
		double x4 = (pos.getX() + dir.getX());
		double y4 = (pos.getY() + dir.getY());

		double denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
		if (denominator == 0)	return null;

		double t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / (double) denominator;
		double u = -(((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / (double) denominator);

		if (t > 0 && t < 1 && u > 0) {
			return new Point((int) (x1 + t * (x2 - x1)), (int) (y1 + t * (y2 - y1)));
		} else {
			return null;
		}
	}

	public void updateIntersection(LinkedList<Boundary> bounds) {
		Point closest = null;
		double distanceMin = Double.MAX_VALUE;
		for (Boundary bound : bounds) {
			Point currentIntersection = cast(bound);
			if (currentIntersection != null) {
				double distance = currentIntersection.getLength(pos);
				if (distance < distanceMin) {
					closest = currentIntersection;
					distanceMin = Math.min(distanceMin, distance);
				}
			}
			if (closest != null) {
				intersection = closest;
			}
		}
	}
	public static void updateIntersection(LinkedList<Ray> rays, LinkedList<Boundary> bounds) {
		for (Ray ray : rays) {
			ray.updateIntersection(bounds);
		}
	}

	public Point getIntersection() {return intersection;}
	public void resetIntersection() {intersection = null;}

	@Override
	public String toString() {
		return "Pos = "+pos.toString()+"\nDir = "+dir.toString();
	}
}