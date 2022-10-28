package model;

import model.Point;

public class Boundary {

	private Point start;
	private Point end;

	public Boundary(Point start, Point end) {
		this.start = start;
		this.end = end;
	}
	public Boundary(double x1, double y1, double x2, double y2) {
		start = new Point(x1, y1);
		end = new Point(x2, y2);
	}

	public Point getStart() {return start;}
	public Point getEnd() {return end;}

}