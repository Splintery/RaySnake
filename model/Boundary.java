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
		this(new Point(x1, y1), new Point(x2, y2));
	}

	public Point getStart() {return start;}
	public Point getEnd() {return end;}

	@Override
	public String toString() {
		return "Start :"+start+" and End :"+end;
	}
	@Override
	public boolean equals(Object o) {
		if (o == this)	return true;
		if (!(o instanceof Boundary))	return false;
		return ((Boundary) o).start.equals(start) && ((Boundary) o).end.equals(end);
	}
}