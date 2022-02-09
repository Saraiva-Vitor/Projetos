package com.svstudios.world;

import java.awt.Graphics;
import java.awt.image.BufferedImage;

import com.svstudios.main.Game;

public class Tile {

	//Tiles
	public static BufferedImage TILE_GRASSFLOOR1 = Game.spritesheet.getSprite(0, 0, 16, 16);
	public static BufferedImage TILE_GRASSFLOOR2 = Game.spritesheet.getSprite(16, 0, 16, 16);
	public static BufferedImage TILE_WOODFLOOR = Game.spritesheet.getSprite(0, 64, 16, 16);
	public static BufferedImage TILE_STONEFLOOR = Game.spritesheet.getSprite(0, 16, 16, 16);
	public static BufferedImage TILE_STONEWALL = Game.spritesheet.getSprite(16, 16, 16, 16);
	public static BufferedImage TILE_WOODENWALL1 = Game.spritesheet.getSprite(16, 64, 16, 16);
	public static BufferedImage TILE_WOODENWALL2 = Game.spritesheet.getSprite(0, 80, 16, 16);
	public static BufferedImage TILE_WOODENWALL3 = Game.spritesheet.getSprite(16, 80, 16, 16);
	public static BufferedImage TILE_BLANK = Game.spritesheet.getSprite(16, 32, 16, 16);
	public static BufferedImage TILE_STONEPATH = Game.spritesheet.getSprite(0,96, 16, 16);
	public static BufferedImage TILE_WATER = Game.spritesheet.getSprite(16,128, 16, 16);
	
	public boolean show = false;

	private BufferedImage sprite;
	private int x,y;
	
	public Tile(int x, int y, BufferedImage sprite) {
		this.x = x;
		this.y = y;
		this.sprite = sprite;
	}
	
	public void render(Graphics g) {
		//if(show) {
			g.drawImage(sprite, x - Camera.x, y - Camera.y, null);
		//}
	}
	
}
