package controller;

import view.GameFrame;
import view.GamePanel2D;

import model.Boundary;
import model.Character;
import model.Ray;

import constant.Constant;

import input.MouseInputs;

import java.awt.Point;
import java.util.LinkedList;


public class Controller implements Runnable {

	private GameFrame gameFrame;
	private GamePanel2D gamePanel2D;
	private Thread mainThread;

	private Character character;
	private LinkedList<Boundary> bounds;

	private int UPS = 200;
	private double timePerUpdate = 1000000000.0 / UPS;
	private final int FPS = 144;
	private double timePerFrame = 1000000000.0 / FPS;
	private boolean suspended = false;

	public Controller() {
		double w = Constant.WIDTH / 2;
		double h = Constant.HEIGHT / 2;

		

		bounds = new LinkedList<Boundary>();
		
		bounds.add(new Boundary(-w, -h, -w, h));
		bounds.add(new Boundary(-w, h, w, h));
		bounds.add(new Boundary(w, -h, w, h));
		bounds.add(new Boundary(-w, -h, w, -h));

		bounds.add(new Boundary(10, 5, 10, -15));
		bounds.add(new Boundary(35, 5, 35, -15));
		bounds.add(new Boundary(10, 5, 35, 5));
		bounds.add(new Boundary(10, -15, 35, -15));

		character = new Character(this, w, h);

		gamePanel2D = new GamePanel2D(this);
		gamePanel2D.addMouseMotionListener(new MouseInputs(this));
		gameFrame = new GameFrame(this, gamePanel2D);
		mainThread = new Thread(this);
		mainThread.start();
	}

	public Character getCharacter() {return character;}
	public LinkedList<Boundary> getBounds() {return bounds;}

	@Override
	public void run() {
		// On a 2 champs pour traquer les updates
		int updates = 0;
		double updateTracker = 0;
		// Ainsi que 2 champs pour traquer les frames
		int frames = 0;
		double frameTracker = 0;

		int cycle = 0;


		// Ces 2 champs sont pour compter le temps en nanoSeconde entre deux passage dans 
		// la boucle while
		long lastCheck = System.currentTimeMillis();
		long previousTime = System.nanoTime();
		

		while(true) {
			long currentTime = System.nanoTime();

			updateTracker += (currentTime - previousTime) / timePerUpdate;
			// Si le jeu est en pause alors suspended = true
			if (updateTracker >= 1) {
				if (!suspended) {
					if (cycle > 1000) {
						character.setTarget();
						cycle = 0;
					}
					update();
					updates++;
				}
				cycle++;
				updateTracker--;
			}

			frameTracker += (currentTime - previousTime) / timePerFrame;
			// On ne mets jamais en pause l'affichage
			if (frameTracker >= 1) {
				gameFrame.repaint();
				frames++;
				frameTracker--;
			}

			// On ne rentre dans ce if que si au moins 1 seconde viens de passer
			// Puis on affiche les FPS ainsi que les UPS
			if (System.currentTimeMillis() - lastCheck >= 1000) {
				lastCheck = System.currentTimeMillis();
				// System.out.printf("FPS :%d\nUPS :%d\n", frames, updates);	
				updates = 0;
				frames = 0;
			}
			previousTime = currentTime;

		}
	}

	public void update() {
		character.betterUpdate();
	}
}