package model;

public class Cell {
	public Cell NORTH;
	public Cell SOUTH;
	public Cell EAST;
	public Cell WEST;

	/*	index 0 : NORTH
		index 1 : SOUTH
		index 2 : EAST
		index 3 : WEST*/
	private Boundary[] edges = new Boundary[4];

	private Point pos;

	public Cell(Point pos) {
		this.pos = pos;
	}

	public boolean equals(Point pos) {
		return this.pos == pos;
	}
}