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

	public Point getPoint() {return this;}
	public double getX() {return x;}
	public double getY() {return y;}
	public void setX(double newX) {x = newX;}
	public void setY(double newY) {y = newY;}

	@Override
	public String toString() {
		return "[x = +"+x+"; y = "+y+"]";
	}

	public boolean equals(Point p) {
		return x == p.getX() && y == p.getY();
	}
}