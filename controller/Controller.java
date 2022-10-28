package controller;

import view.GameFrame;
import view.GamePanel2D;

import model.Boundary;
import model.Character;
import model.Ray;

import input.MouseInputs;

import java.awt.Point;
import java.util.LinkedList;


public class Controller implements Runnable {

	private GameFrame gameFrame;
	private GamePanel2D gamePanel2D;
	private Thread mainThread;

	private Character character;
	private Ray ray;
	private LinkedList<Boundary> bounds;

	private int UPS = 250;
	private double timePerUpdate = 1000000000.0 / UPS;
	private final int FPS = 144;
	private double timePerFrame = 1000000000.0 / FPS;
	private boolean suspended = false;

	public Controller() {

		character = new Character(this, 720, 480);

		bounds = new LinkedList<Boundary>();
		bounds.add(new Boundary(0, 960, 1440, 960));
		bounds.add(new Boundary(0, 0, 0, 960));
		bounds.add(new Boundary(0, 0, 1440, 0));
		bounds.add(new Boundary(1440, 0, 1440, 960));

		bounds.add(new Boundary(300, 50, 300, 700));
		bounds.add(new Boundary(600, 50, 500, 800));
		bounds.add(new Boundary(300, 50, 600, 50));

		bounds.add(new Boundary(573, 783, 299, 986));

		gamePanel2D = new GamePanel2D(this);
		gamePanel2D.addMouseMotionListener(new MouseInputs(this));
		gameFrame = new GameFrame(this, gamePanel2D);
		mainThread = new Thread(this);
		mainThread.start();
	}

	public Character getCharacter() {return character;}
	public Ray getRay() {return ray;}
	public LinkedList<Boundary> getBoundarys() {return bounds;}

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
					character.move();
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
		character.update();
	}
}