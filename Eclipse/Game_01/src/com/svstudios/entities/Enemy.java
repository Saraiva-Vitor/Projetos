package com.svstudios.entities;

import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.image.BufferedImage;
import java.util.Random;

import com.svstudios.main.Game;
import com.svstudios.main.Sound;
import com.svstudios.world.AStar;
import com.svstudios.world.Camera;
import com.svstudios.world.Vector2i;

public class Enemy extends Entity{
	
	public static double speed = 0.4;
		
	private int frames = 0,maxFrames = 20,index = 0,maxIndex = 2;
	
	private BufferedImage[] sprites;
	
	private int life = 10;
	
	private boolean isDamaged = false;
	private int damageFrames = 10,damageCurrent = 0;

	public Enemy(int x, int y, int width, int height, BufferedImage[] sprite) {
		super(x, y, width, height, null);
		sprites = new BufferedImage[3];
		this.sprites[0] = sprite[0];
		this.sprites[1] = sprite[1];
		this.sprites[2] = sprite[2];
	}

	public void tick(){
		depth = 0;
		maskx = 5;
		masky = 5;
		mwidth = 8;
		mheight = 8;
		if(this.calculateDistance(this.getX(), this.getY(), Game.player.getX(), Game.player.getY()) < 100){
			if(!isCollidingWithPlayer()) {
				if(path == null || path.size() == 0) {
					Vector2i start = new Vector2i((int)x/16,(int)y/16);
					Vector2i end = new Vector2i((int)Game.player.x/16,(int)Game.player.y/16);
					path = AStar.findPath(Game.world, start, end);
				}
			}else {
				if(Game.rand.nextInt(100) < 10){
					Sound.hurtEffect.play();
					Game.player.life-=Game.rand.nextInt(3);
					Game.player.isDamaged = true;
					Sound.hurtEffect.play();
					//System.out.println("Vida: "+ Game.player.life);
				}
			}
			if(new Random().nextInt(100) < 60)
				followPath(path);
			if(new Random().nextInt(100) < 5) {
				Vector2i start = new Vector2i((int)x/16,(int)y/16);
				Vector2i end = new Vector2i((int)Game.player.x/16,(int)Game.player.y/16);
				path = AStar.findPath(Game.world, start, end);
			}
		}
			frames++;
			if(frames == maxFrames) {
				frames = 0;
				index++;
				if(index > maxIndex)
					index = 0;
			}
			
			collidingSlash();
			
			if(life <= 0) {
				destroySelf();
				return;
			}
			
			if(isDamaged) {
				this.damageCurrent++;
				if(this.damageCurrent == this.damageFrames) {
					this.damageCurrent = 0;
					this.isDamaged = false;
				}
			}
		
		
	}
	
	public void destroySelf() {
		Game.enemies.remove(this);
		Game.entities.remove(this);
	}
	
	public void collidingSlash() {
		for(int i = 0; i < Game.slashs.size(); i++) {
			Entity e = Game.slashs.get(i);
				if(Entity.isColliding(this,e)) {
					isDamaged = true;
					life--;
					Game.slashs.remove(i);
					return;
				}
		}
		
		
	}
	
	public boolean isCollidingWithPlayer(){
		Rectangle enemyCurrent = new Rectangle(this.getX() + maskx,this.getY() + masky,mwidth,mheight);
		Rectangle player = new Rectangle(Game.player.getX(),Game.player.getY(),16,16);
		
		return enemyCurrent.intersects(player);
	}
	
	public void render(Graphics g) {
		if(!isDamaged)
			g.drawImage(sprites[index], this.getX() - Camera.x,this.getY() - Camera.y,null);
		else
			g.drawImage(Entity.ENEMY_FEEDBACK, this.getX() - Camera.x,this.getY() - Camera.y,null);
		//g.setColor(Color.red);
		//g.fillRect(this.getX() + maskx - Camera.x, this.getY() + masky - Camera.y, mwidth,mheight);
	}
	
	
}
