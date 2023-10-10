package model;

public class Point {
	private double x;
	private double y;

	public Point(double x, double y) {
		this.x = x;
		this.y = y;
	}
	public Point(Point point) {
		this(point.getX(), point.getY());
	}

	public double getLength(Point p) {
		return Math.sqrt(Math.pow(p.x - x, 2) + Math.pow(p.y - y, 2));
	}
	public static double crossProduct(Point p1, Point p2) {
		return p1.x * p2.y - p1.y * p2.x;
	}
	// substracts p to "this"
	public static Point substractPoint(Point p1, Point p2) {
		return new Point(p1.x - p2.x, p1.y - p2.y);
	}

	public Point getPoint() {return this;}
	public double getX() {return x;}
	public double getY() {return y;}
	public void setX(double newX) {x = newX;}
	public void setY(double newY) {y = newY;}

	@Override
	public String toString() {
		return "[x = +"+x+"; y = "+y+"]";
	}
	@Override
	public boolean equals(Object o) {
		if (o == this)	return true;
		if (!(o instanceof Point))	return false;
		return x == ((Point) o).x && y == ((Point) o).y;
	}
}