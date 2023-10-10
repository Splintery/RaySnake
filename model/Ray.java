package model;

import java.util.List;
import java.util.ArrayList;
import constant.Constant;


public class Ray {

	private Point pos;
	private Point dir;

	private Point intersection = null;
	private Boundary pointerBound;

	public Ray(Point pos, Point dir, Boundary pointerBound) {
		this.pos = pos;
		this.dir = dir;
		this.pointerBound = pointerBound;
	}
	public Ray(int x1, int y1, int x2, int y2, Boundary pointerBound) {
		this(new Point(x1, y1), new Point(x2, y2), pointerBound);
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
		double x4 = pos.getX() + dir.getX();
		double y4 = pos.getY() + dir.getY();

		double denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
		if (denominator == 0)	return null;

		double t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / (double) denominator;
		double u = -(((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / (double) denominator);

		if (t > 0 && t < 1 && u > 0) {
			return new Point((x1 + t * (x2 - x1)), (y1 + t * (y2 - y1)));
		} else {
			return null;
		}
	}
	public Point castSegment(Boundary bound) {
		Point p = bound.getStart();
		Point p2 = bound.getEnd();
		Point q = pos;
		Point q2 = dir;

		Point r = Point.substractPoint(p2, p);
		Point s = Point.substractPoint(q2, q);

		Double numerator = Point.crossProduct(Point.substractPoint(q, p), r);
		Double denominator = Point.crossProduct(r, s);


		// if (numerator == 0 && denominator == 0) {
		// 	if (p.equals(q) || p.equals(q2) || p2.equals(q) || p2.equals(q2)) {
		// 		return true;
		// 	}
		// 	return
		// 		!((q.x - p.x < 0) &&
		// 		(q.x - p2.x < 0) &&
		// 		(q2.x - p.x < 0) &&
		// 		(q2.x - p2.x < 0)) ||
		// 		!((q.y - p.y < 0) &&
		// 		(q.y - p2.y < 0) &&
		// 		(q2.y - p.y < 0) &&
		// 		(q2.y - p2.y < 0));
		// }

		// Lines are paralell
		if (denominator == 0) {
			return null;
		}

		double u = numerator / denominator;
		double t = Point.crossProduct(Point.substractPoint(q, p), s) / denominator;

		if ((t >= 0) && (t <= 1) && (u >= 0) && (u <= 1)) {
			return new Point(p.getX() + t * (p2.getX() - p.getX()), p.getY() + t * (p2.getY() - p.getY()));
		} else {
			return null;
		}


	}

	public void updateIntersection(List<Boundary> bounds) {
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
	public static void updateIntersection(List<Ray> rays, List<Boundary> bounds) {
		for (Ray ray : rays) {
			ray.updateIntersection(bounds);
		}
	}
	public void updateDirection(List<Boundary> bounds) {
		Point closest = null;
		double distanceMin = Double.POSITIVE_INFINITY;
		for (Boundary bound : bounds) {
			if (!bound.equals(pointerBound)) {
				// Ici on cast en le prenant pour un segment alors que pour avoir
				// un champs de vision complet il faut que les vecteurs créés autour 
				// des début et fin de "bounds" soit castés comme des droites
				// (qui vont vers l'infini)
				Point currentIntersection = castSegment(bound);
				if (currentIntersection != null) {
					double distance = currentIntersection.getLength(pos);
					if (distance < distanceMin) {
						closest = currentIntersection;
						distanceMin = Math.min(distanceMin, distance);
					}
				}
				if (closest != null) {
					// System.out.println("We found a closer intersection !(BINGO)");
					// System.out.println("Our Ray origin is :"+pos);
					// System.out.println("Insted of (currentDir) :"+dir+"\nWe have (newDir) :"+closest);
					// System.out.println("This rays pointerBound is ("+pointerBound+") and his new found intersection is ("+bound+")");
					dir = closest;
				}
			}
		}
	}
	public static void updateDirection(List<Ray> rays, List<Boundary> bounds) {
		for (Ray ray : rays) {
			ray.updateDirection(bounds);
		}
	}

	public Point getIntersection() {return intersection;}
	public void resetIntersection() {intersection = null;}

	public static List<Point> getConvertedListOfPointsFromRays(List<Ray> rays) {
		List<Point> res = new ArrayList<Point>();
		for (Ray r : rays) {
			res.add(Constant.convertToPixels(r.getDir()));
		}
		return res;
	}
	public static List<Point> tmp(List<Ray> rays) {
		List<Point> res = new ArrayList<Point>();
		for (Ray r : rays) {
			res.add(r.getDir());
		}
		return res;
	}

	@Override
	public String toString() {
		return "Pos = "+pos.toString()+" and Dir = "+dir.toString();
	}
}