package com.svstudios.main;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.FontFormatException;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Point;
import java.awt.Toolkit;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.image.BufferStrategy;
import java.awt.image.BufferedImage;
import java.awt.image.DataBufferInt;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

import javax.imageio.ImageIO;
import javax.swing.JFrame;

import com.svstudios.entities.AxeSlash;
import com.svstudios.entities.Enemy;
import com.svstudios.entities.Entity;
import com.svstudios.entities.Npc;
import com.svstudios.entities.Player;
import com.svstudios.graficos.Spritesheet;
import com.svstudios.graficos.UI;
import com.svstudios.world.World;

public class Game extends Canvas implements Runnable,KeyListener,MouseListener,MouseMotionListener{

	private static final long serialVersionUID = 1L;
	public static JFrame frame;
	private Thread thread;
	private boolean isRunning = true;
	public static final int WIDTH = 240;
	public static final int HEIGHT = 160;
	public static final int SCALE = 3;
	
	public static int CUR_LEVEL = 1;
	public static int MAX_LEVEL = 2;
	private BufferedImage image;
	
	public static List<Entity> entities;
	public static List<Enemy> enemies;
	public static List<AxeSlash> slashs;
	
	public static Spritesheet spritesheet;
	
	public static World world;
	
	public static Player player;
	
	public static Random rand;
		
	public UI ui;
		
	public InputStream stream = ClassLoader.getSystemClassLoader().getResourceAsStream("Bitmgothic.ttf");
	public static Font newfont;
	
	public static String gameState = "MENU";
	private boolean showMessageGameOver = true;
	private int framesGameOver = 0;
	private boolean restartGame = false;
	
	public Menu menu;
	public static int[] pixels;
	public static int[] lightMapPixels;
	public BufferedImage lightmap;
	public static int[] minimapaPixels;
	
	public static BufferedImage minimapa;
	
	public int mx,my;
	
	public static boolean saveGame = false;
	
	public Npc npc;
	
	public Game(){
		rand = new Random();
		addKeyListener(this);
		addMouseListener(this);
		addMouseMotionListener(this);
		
		//Tamanho da Tela
		
		//Fullscreen
		//setPreferredSize(new Dimension(Toolkit.getDefaultToolkit().getScreenSize()));
		
		//Modo Janela
		setPreferredSize(new Dimension(WIDTH*SCALE,HEIGHT*SCALE));
		
		initFrame();
		//Inicializando objetos.
		ui = new UI();
		image = new BufferedImage(WIDTH,HEIGHT,BufferedImage.TYPE_INT_RGB);
		try {
			lightmap = ImageIO.read(getClass().getResource("/lightmap.png"));
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		lightMapPixels = new int[lightmap.getWidth() * lightmap.getHeight()];
		lightmap.getRGB(0, 0, lightmap.getWidth(), lightmap.getHeight(), lightMapPixels, 0, lightmap.getWidth());
		pixels =((DataBufferInt)image.getRaster().getDataBuffer()).getData();
		entities = new ArrayList<Entity>();
		enemies = new ArrayList<Enemy>();
		slashs = new ArrayList<AxeSlash>();
		
		spritesheet = new Spritesheet("/spritesheet.png");
		player = new Player(0,0,16,32,spritesheet.getSprite(32, 0,16,32));
		entities.add(player);
		world = new World("/level1.png");
		
		npc = new Npc(20,210,16,32,spritesheet.getSprite(0, 32, 16, 32));
		entities.add(npc); 
		
		minimapa = new BufferedImage(World.WIDTH, World.HEIGHT, BufferedImage.TYPE_INT_RGB);
		minimapaPixels =((DataBufferInt)minimapa.getRaster().getDataBuffer()).getData();
		
		try {
			newfont = Font.createFont(Font.TRUETYPE_FONT, stream).deriveFont(48f);
		} catch (FontFormatException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		menu = new Menu();
	}
	
	public void initFrame(){
		frame = new JFrame("Against Darkness");
		frame.add(this);
		
		//Fullscreen
		//frame.setUndecorated(true);
		
		frame.setResizable(false);
		frame.pack();
		Image imagem = null;
		try {
			imagem = ImageIO.read(getClass().getResource("/icon.png"));
		}catch (IOException e) {
			e.printStackTrace();
		}
		Toolkit toolkit = Toolkit.getDefaultToolkit();
		Image image = toolkit.getImage(getClass().getResource("/cursor.png"));
		Cursor c = toolkit.createCustomCursor(image, new Point(0,0), "img");
		frame.setCursor(c);
		frame.setIconImage(imagem);
		frame.setAlwaysOnTop(true);
		frame.setLocationRelativeTo(null);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
	
	public synchronized void start(){
		thread = new Thread(this);
		isRunning = true;
		thread.start();
	}
	
	public synchronized void stop(){
		isRunning = false;
		try {
			thread.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String args[]){
		Game game = new Game();
		game.start();
	}
	
	public void tick(){
		if(gameState == "NORMAL") {
			if(Game.saveGame){
				Game.saveGame = false;
				String[] opt1 = {"level","posiçãoX","posiçãoY"};
				int[] opt2 = {Game.CUR_LEVEL,player.getX(),player.getY()};
				Menu.saveGame(opt1,opt2,10);
				System.out.println("Jogo Salvo!");
			}
			this.restartGame = false;	
			for(int i = 0; i < entities.size(); i++) {
				Entity e = entities.get(i);
				e.tick();
			}
		
			for(int i = 0; i < slashs.size(); i++) {
				slashs.get(i).tick();
			}
		
			if(enemies.size() == 0) {
				//Avançar para o próximo level após matar todos os inimigos!
				CUR_LEVEL++;
				if(CUR_LEVEL > MAX_LEVEL){
					CUR_LEVEL = 1;
				}
				String newWorld = "level"+CUR_LEVEL+".png";
				//System.out.println(newWorld);
				World.restartGame(newWorld);
			}
			
		}else if(gameState == "GAME_OVER") {
			this.framesGameOver++;
			if(this.framesGameOver == 30) {
				this.framesGameOver = 0;
				if(this.showMessageGameOver)
					this.showMessageGameOver = false;
					else
						this.showMessageGameOver = true;
			}
			
			if(restartGame) {
				this.restartGame = false;
				Game.gameState = "NORMAL";
				CUR_LEVEL = 1;
				String newWorld = "level"+CUR_LEVEL+".png";
				//System.out.println(newWorld);
				World.restartGame(newWorld);
			}
		}else if(gameState == "MENU") {
			player.updateCamera();
			menu.tick();
		}
	}
	
	/*public void drawRectangleExample(int xoff, int yoff) {
		for(int xx = 0; xx < 32; xx++) {
			for(int yy = 0; yy < 32; yy++) {
				int xOff = xx + xoff;
				int yOff = yy + yoff;
				if(xOff < 0 || yOff < 0 || xOff >= WIDTH || yOff >= HEIGHT) {
					continue;
				}
				pixels[xOff + (yOff *WIDTH)] = 0xff0000;
			}
		}
	}*/
	
	public void applyLight() {
		for(int xx = 0; xx < Game.WIDTH; xx++) {
			for(int yy = 0; yy < Game.HEIGHT; yy++) {
				if(lightMapPixels[xx+(yy * Game.WIDTH)] == 0xffffffff) {
					int pixel = Pixel.getLightBlend(pixels[xx + (yy*WIDTH)], 0xFF909090, 0);
					 pixels[xx + (yy *Game.WIDTH)] = pixel;
				}
			}
		}
	}
	
	public void render(){
		BufferStrategy bs = this.getBufferStrategy();
		if(bs == null){
			this.createBufferStrategy(3);
			return;
		}
		Graphics g = image.getGraphics();
		g.setColor(new Color(0,0,0));
		g.fillRect(0, 0,WIDTH,HEIGHT);
		
		/*Renderização do jogo*/
		//Graphics2D g2 = (Graphics2D) g;
		world.render(g);
		Collections.sort(entities, Entity.nodeSorter);
		for(int i = 0; i < entities.size(); i++) {
			Entity e = entities.get(i);
			e.render(g);
		}
		for(int i = 0; i < slashs.size(); i++) {
			slashs.get(i).render(g);
		}
		
		ui.render(g);
		/***/
		g.dispose();
		//applyLight();
		g = bs.getDrawGraphics();
		
		//Fullscreen
		//g.drawImage(image, 0, 0, Toolkit.getDefaultToolkit().getScreenSize().width, Toolkit.getDefaultToolkit().getScreenSize().height,null);
		
		//Modo Janela
		g.drawImage(image, 0, 0,WIDTH*SCALE,HEIGHT*SCALE,null);
		
		if(gameState == "GAME_OVER") {
			Graphics2D g2 = (Graphics2D) g;
			g2.setColor(new Color(0,0,0,100));
			g2.fillRect(0, 0, WIDTH*SCALE, HEIGHT*SCALE);
			g.setFont(newfont);
			g.setColor(Color.red);
			g.drawString("Game Over",(WIDTH*SCALE) / 2 - 110,(HEIGHT* SCALE) / 2 - 20);
			g.setFont(newfont.deriveFont(32f));
			g.setColor(Color.white);
			if(showMessageGameOver)
				g.drawString(">Pressione Enter para reiniciar<",(WIDTH*SCALE) / 2 - 230,(HEIGHT* SCALE) / 2 + 40);
		}else if(gameState == "MENU") {
			menu.render(g);
		}
		/*Rotacionar Objetos
		
		Graphics2D g2 = (Graphics2D) g;
		double angleMouse = Math.atan2(200+25 - my, 200+25 - mx);
		g2.rotate(angleMouse,200+25,200+25);
		g.setColor(Color.red);
		g.fillRect(200,200,50,50);
		
		World.renderMiniMap();
		g.drawImage(minimapa,10,10,World.WIDTH*5,World.HEIGHT*5,null);
		*/
		bs.show();
	}
	
	public void run() {
		requestFocus();
		long lastTime = System.nanoTime();
		double amountOfTicks = 60.0;
		double ns = 1000000000 / amountOfTicks;
		double delta = 0;
		int frames = 0;
		double timer = System.currentTimeMillis();
		requestFocus();
		while(isRunning){
			long now = System.nanoTime();
			delta+= (now - lastTime) / ns;
			lastTime = now;
			if(delta >= 1) {
				tick();
				render();
				frames++;
				delta--;
			}
			
			if(System.currentTimeMillis() - timer >= 1000){
				System.out.println("FPS: "+ frames);
				frames = 0;
				timer+=1000;
			}
			
		}
		
		stop();
	}

	@Override
	public void keyPressed(KeyEvent e) {
		if(e.getKeyCode() == KeyEvent.VK_ENTER) {
			npc.showMessage = false;
		}
		
		if(e.getKeyCode() == KeyEvent.VK_RIGHT ||
				e.getKeyCode() == KeyEvent.VK_D){
			player.right = true;
		}else if(e.getKeyCode() == KeyEvent.VK_LEFT ||
				e.getKeyCode() == KeyEvent.VK_A){
			player.left = true;
		}
		
		if(e.getKeyCode() == KeyEvent.VK_UP ||
				e.getKeyCode() == KeyEvent.VK_W){
			player.up = true;
			if(gameState == "MENU") {
				menu.up = true;
			}
		}else if(e.getKeyCode() == KeyEvent.VK_DOWN ||
				e.getKeyCode() == KeyEvent.VK_S) {
			player.down = true;
			
			if(gameState == "MENU") {
				menu.down = true;
			}
			
		}
		
		if(e.getKeyCode() == KeyEvent.VK_Z){
			player.attack = true;
		}
		
		if(e.getKeyCode() == KeyEvent.VK_ENTER) {
			this.restartGame = true;
			if(gameState == "MENU") {
				menu.enter = true;
			}
		}
		
		if(e.getKeyCode() == KeyEvent.VK_ESCAPE) {
			gameState = "MENU";
			Menu.pause = true;
		}
		
	}

	@Override
	public void keyReleased(KeyEvent e) {
		if(e.getKeyCode() == KeyEvent.VK_RIGHT ||
				e.getKeyCode() == KeyEvent.VK_D){
			player.right = false;
		}else if(e.getKeyCode() == KeyEvent.VK_LEFT ||
				e.getKeyCode() == KeyEvent.VK_A){
			player.left = false;
		}
		
		if(e.getKeyCode() == KeyEvent.VK_UP ||
				e.getKeyCode() == KeyEvent.VK_W){
			player.up = false;
		}else if(e.getKeyCode() == KeyEvent.VK_DOWN ||
				e.getKeyCode() == KeyEvent.VK_S) {
			player.down = false;
		}
		
	}

	@Override
	public void keyTyped(KeyEvent e) {
		
	}

	@Override
	public void mouseClicked(MouseEvent arg0) {
		
	}

	@Override
	public void mouseEntered(MouseEvent arg0) {
		
	}

	@Override
	public void mouseExited(MouseEvent arg0) {
		
	}

	@Override
	public void mousePressed(MouseEvent e) {
		player.mouseAttack = true;
		player.mx = (e.getX() / 3);
		player.my = (e.getY() / 3);
	}

	@Override
	public void mouseReleased(MouseEvent arg0) {
		
	}

	@Override
	public void mouseDragged(MouseEvent e) {
		
	}

	@Override
	public void mouseMoved(MouseEvent e) {
		this.mx = e.getX();
		this.my = e.getY();
	}

	
}
