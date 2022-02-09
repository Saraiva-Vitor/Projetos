package com.svstudios.entities;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.image.BufferedImage;

import com.svstudios.main.Game;
import com.svstudios.world.Camera;
import com.svstudios.world.World;

public class AxeSlash  extends Entity{

	private double dx;
	private double dy;
	private double spd = 4;
	
	private int life = 5, curLife = 0;
	
	public AxeSlash(int x, int y, int width, int height, BufferedImage sprite, double dx, double dy) {
		super(x, y, width, height, sprite);
		this.dx = dx;
		this.dy = dy;
	}
	
	public void tick() {
		if(World.isFreeDynamic((int)(x+(dx*spd)), (int)(y+(dy*spd)), 7, 7)) {
			x+=dx*spd;
			y+=dy*spd;
		}else {
			Game.slashs.remove(this);
			World.generateParticles(100, (int)x, (int)y);
			return;
		}
		curLife++;
		if(curLife == life) {
			Game.slashs.remove(this);
			return;
		}
	}
	
	public void render(Graphics g) {
		g.setColor(Color.red);
		g.fillOval(this.getX() - Camera.x,this.getY() - Camera.y, width, height);
	}
	
}
