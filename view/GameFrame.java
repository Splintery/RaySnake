package view;

import controller.Controller;
import constant.Constant;

import javax.swing.JFrame;

public class GameFrame extends JFrame {

	private Controller controller;

	private GamePanel2D gamePanel2D;

	public GameFrame(Controller controller, GamePanel2D gamePanel2D) {
		this.controller = controller;
		this.gamePanel2D = gamePanel2D;
		frameSetUp(Constant.WINDOW_WIDTH, Constant.WINDOW_HEIGHT);
	}

	private void frameSetUp(int width, int height) {
		setTitle("No Name Ray Game");
		setSize(width, height);
		// setResizable(false);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		getContentPane().add(gamePanel2D);
		setLocationRelativeTo(null);
		setVisible(true);
	}
}