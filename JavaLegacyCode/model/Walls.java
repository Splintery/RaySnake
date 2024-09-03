package model;

import java.util.LinkedList;
import java.awt.Rectangle;

public class Walls {
	LinkedList<Cell> cells;

	Rectangle boardDimension;

	public Walls(int x, int y, int width, int height) {
		boardDimension = new Rectangle(x, y, width, height);
	}

	public void addCell(Point pos) {
		for (Cell c : cells) {
			if (c.equals(pos))	return;
		}
		cells.add(new Cell(pos));
	}
}