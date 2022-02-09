package com.svstudios.entities;

import java.awt.Graphics;
import java.awt.image.BufferedImage;
import com.svstudios.main.Game;
import com.svstudios.world.Camera;
import com.svstudios.world.World;

public class Player extends Entity{

	public boolean right,left,up,down;
	public int right_dir = 0, left_dir = 1, up_dir = 2, down_dir = 4;
	public int dir = down_dir;
	public double speed = 1;
	 
	private int frames = 0,maxFrames = 10,index = 0,maxIndex = 3;
	private boolean moved = false;
	private BufferedImage[] rightPlayer;
	private BufferedImage[] leftPlayer;
	private BufferedImage[] upPlayer;
	private BufferedImage[] downPlayer;
	
	private BufferedImage playerDamage;
	
	public boolean hasAxe = false;
	
	public static int stamina = 0;
	public static int maxstamina = 100;
	
	public boolean isDamaged = false;
	private int damageFrames = 0;
	
	public boolean attack = false,mouseAttack = false;
	
	public double life = 100, maxlife =100;
	public int mx,my;
	
	public Player(int x, int y, int width, int height, BufferedImage sprite) {
		super(x, y, width, height, sprite);
		
		rightPlayer = new BufferedImage[4];
		leftPlayer = new BufferedImage[4];
		upPlayer = new BufferedImage[4];
		downPlayer = new BufferedImage[4];
		playerDamage = Game.spritesheet.getSprite(96, 16, 16, 32);
		for(int i = 0; i < 4; i++) {
			rightPlayer[i] = Game.spritesheet.getSprite(32 + (i*16),0,16,32);
		}
		for(int i = 0; i < 4; i++) {
			leftPlayer[i] = Game.spritesheet.getSprite(32 + (i*16),32,16,32);
		}
		for(int i = 0; i < 4; i++) {
			upPlayer[i] = Game.spritesheet.getSprite(32 + (i*16),64,16,32);
		}
		for(int i = 0; i < 4; i++) {
			downPlayer[i] = Game.spritesheet.getSprite(32 + (i*16),96,16,32);
		}
	}

	public void revealMap() {
		int xx = (int) (x/16);
		int yy = (int) (y/16);
		
		World.tiles[xx+yy*World.WIDTH].show = true;
		
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				World.tiles[xx-i+(yy-j)*World.WIDTH].show = true;
				World.tiles[xx+i+(yy+j)*World.WIDTH].show = true;
				World.tiles[xx+i+(yy-j)*World.WIDTH].show = true;
				World.tiles[xx-i+(yy+j)*World.WIDTH].show = true;
			}
		}				
	}
	
	public void tick() {		
		
		//revealMap();
		
		depth = 1;
		moved = false;
		if(right && World.isFree((int)(x+speed),this.getY()+16)) {
			moved = true;
			dir = right_dir;
			x+=speed;
		}
		if(left && World.isFree((int)(x-speed),this.getY()+16)) {
			moved = true;
			dir = left_dir;
			x-=speed;
		}
		if(up && World.isFree(this.getX(),(int)(y+16-speed))) {
			moved = true;
			dir = up_dir;
			y-=speed;
		}
		if(down && World.isFree(this.getX(),(int)(y+16+speed))) {
			moved = true;
			dir = down_dir;
			y+=speed;
		}
		
		if(moved) {
			frames++;
			if(frames == maxFrames){
				frames = 0;
				index++;
				if(index > maxIndex) {
					index = 0;
				}
			}
		}
		
		checkCollisionHeart();
		checkCollisionPotion();
		checkCollisionAxe();
		checkCollisionPortal();
		checkCollisionCheckPoint();

		if(isDamaged) {
			this.damageFrames++;
			if(this.damageFrames == 8) {
				this.damageFrames = 0;
				isDamaged = false;
			}
		}
		
		if(attack) {
			attack = false;
			if(hasAxe && stamina > 0) {
				stamina--;
				int dx = 0;
				int dy = 0;
				int px = 6;
				int py = 6;
				if(dir == right_dir){
					dx = 1;
				}else if(dir == left_dir){
					dx = -1;
				}else if(dir == up_dir) {
					dy = -1;
				}else if(dir == down_dir) {
					dy = 1;
				}
			
				AxeSlash slash = new AxeSlash(this.getX() + px,this.getY() + py,7,7,null,dx,dy);
				Game.slashs.add(slash);
			//System.out.println("Slash!");
			}
		}
		if(mouseAttack) {
			mouseAttack = false;
			if(hasAxe && stamina > 0) {
				stamina--;
				double angle = Math.atan2(my - (this.getY()+8 - Camera.y), mx - (this.getX()+8 - Camera.x));
				double dx = Math.cos(angle);
				double dy = Math.sin(angle);
				int px = 8;
				int py = 8;
							
				AxeSlash slash = new AxeSlash(this.getX() + px,this.getY() + py,7,7,null,dx,dy);
				Game.slashs.add(slash);
			//System.out.println("Mouse Slash!");
			}
		}
		
		if(life <= 0) {
			//Game Over
			life = 0;
			Game.gameState = "GAME_OVER";
		}
		
		updateCamera();
		
	}
	
	public void updateCamera(){
		Camera.x = Camera.clamp(this.getX() - (Game.WIDTH/2), 0, World.WIDTH*World.TILE_SIZE - Game.WIDTH);
		Camera.y = Camera.clamp(this.getY() - (Game.HEIGHT/2), 0, World.HEIGHT*World.TILE_SIZE - Game.HEIGHT);
	}
	
	public void checkCollisionPotion(){
		for(int i = 0;i < Game.entities.size(); i++) {
			Entity e = Game.entities.get(i);
			if(e instanceof Potion) {
				if(Entity.isColliding(this, e)) {
					stamina+=20;
					if(stamina >= 100) {
						stamina = 100;
					}
					//System.out.println("Stamina: " + stamina);
					Game.entities.remove(i);
					return;
				}
			}
		}
	}
	
	public void checkCollisionCheckPoint(){
		for(int i = 0;i < Game.entities.size(); i++) {
			Entity e = Game.entities.get(i);
			if(e instanceof CheckPoint) {
				if(Entity.isColliding(this, e)) {
					if(Game.gameState == "NORMAL") {
						Game.saveGame = true;
					}
					Game.entities.remove(i);
					}
					return;
				}
			}
		}
	
	
	public void checkCollisionPortal(){
		for(int i = 0;i < Game.entities.size(); i++) {
			Entity e = Game.entities.get(i);
			if(e instanceof Portal) {
				if(Entity.isColliding(this, e)) {
						Game.CUR_LEVEL++;
						if(Game.CUR_LEVEL > Game.MAX_LEVEL) {
							Game.CUR_LEVEL = 1;
						}
						String newWorld = "level" + Game.CUR_LEVEL + ".png";
						World.restartGame(newWorld);
					}
					return;
				}
			}
		}
	
	public void checkCollisionHeart() {
		for(int i = 0;i < Game.entities.size(); i++) {
			Entity e = Game.entities.get(i);
			if(e instanceof Heart) {
				if(Entity.isColliding(this, e)) {
					life+=10;
					if(life >= 100) {
						life = 100;
					}
					Game.entities.remove(i);
					return;
				}
			}
		}
	}
	
	public void checkCollisionAxe(){
		for(int i = 0;i < Game.entities.size(); i++) {
			Entity e = Game.entities.get(i);
			if(e instanceof Axe) {
				if(Entity.isColliding(this, e)) {
					hasAxe = true;
					//System.out.println("Com Espada");
					Game.entities.remove(i);
					return;
				}
			}
		}
	}
	
	public void render(Graphics g) {
		if(!isDamaged) {
		if(dir == right_dir) {
			g.drawImage(rightPlayer[index], this.getX() - Camera.x,this.getY() - Camera.y,null);
			if(hasAxe) {
				g.drawImage(Entity.AXE_RIGHT,this.getX() - Camera.x ,this.getY() - Camera.y - 2, null);
			}
		}else if(dir == left_dir) {
			g.drawImage(leftPlayer[index], this.getX() - Camera.x,this.getY() - Camera.y,null);
			if(hasAxe) {
				g.drawImage(Entity.AXE_LEFT,this.getX() - Camera.x - 16,this.getY() - Camera.y - 2, null);
			}
		}else if(dir == down_dir){
			if(hasAxe) {
				g.drawImage(Entity.AXE_FRONT,this.getX() - Camera.x - 7,this.getY() - Camera.y + 1, null);
			}
			g.drawImage(downPlayer[index], this.getX() - Camera.x,this.getY() - Camera.y,null);
		}else if(dir == up_dir) {
			g.drawImage(upPlayer[index], this.getX() - Camera.x,this.getY() - Camera.y,null);
			if(hasAxe) {
				g.drawImage(Entity.AXE_BACK,this.getX() - Camera.x - 7,this.getY() - Camera.y + 1, null);
			}
		}
	}else {
		g.drawImage(playerDamage, this.getX() - Camera.x, this.getY() - Camera.y,null);
	}
	}
	
}
