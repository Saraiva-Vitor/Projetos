package com.svstudios.world;

import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.ArrayList;

import javax.imageio.ImageIO;

import com.svstudios.entities.Enemy;
import com.svstudios.entities.*;
import com.svstudios.graficos.Spritesheet;
import com.svstudios.main.Game;

public class World {
	
	public static Tile[] tiles;
	public static int WIDTH,HEIGHT;
	public static final int TILE_SIZE =16;
	
	public World(String path) {
		
		try {
			BufferedImage map = ImageIO.read(getClass().getResource(path));
			int[] pixels = new int[map.getWidth() * map.getHeight()];
			WIDTH = map.getWidth();
			HEIGHT = map.getHeight();
			tiles = new Tile[map.getWidth() * map.getHeight()];
			map.getRGB(0, 0, map.getWidth(), map.getHeight(), pixels, 0, map.getWidth());
			for(int xx = 0; xx < map.getWidth(); xx++) {
				for(int yy = 0; yy < map.getHeight(); yy++) {
					int pixelAtual = pixels[xx + (yy*map.getWidth())];
					if(Game.CUR_LEVEL == 1) {
						tiles[xx + (yy * WIDTH)] = new FloorTile(xx*TILE_SIZE, yy*TILE_SIZE, Tile.TILE_STONEFLOOR);
					}else if(Game.CUR_LEVEL == 2){
						tiles[xx + (yy * WIDTH)] = new FloorTile(xx*TILE_SIZE, yy*TILE_SIZE, Tile.TILE_GRASSFLOOR1);
					}
					if(pixelAtual == 0xFF000000) {
						//ChãoPedra
						tiles[xx + (yy * WIDTH)] = new FloorTile(xx*TILE_SIZE, yy*TILE_SIZE, Tile.TILE_STONEFLOOR);
					}else if(pixelAtual == 0xFFFFFFFF) {
						//ParedePedra
						tiles[xx + (yy * WIDTH)] = new WallTile(xx*TILE_SIZE, yy*TILE_SIZE, Tile.TILE_STONEWALL);
					}else if(pixelAtual == 0xFF3F7F47) {
						//Chão GRASS
						if(Game.rand.nextInt(100) < 50) {
							tiles[xx + (yy * WIDTH)] = new FloorTile(xx*TILE_SIZE, yy*TILE_SIZE, Tile.TILE_GRASSFLOOR1);
						}else
							tiles[xx + (yy * WIDTH)] = new FloorTile(xx*TILE_SIZE, yy*TILE_SIZE, Tile.TILE_GRASSFLOOR2);
					}else if(pixelAtual == 0xFF808080) {
						tiles[xx + (yy * WIDTH)] = new FloorTile(xx*TILE_SIZE, yy*TILE_SIZE, Tile.TILE_STONEPATH);
					}else if(pixelAtual == 0xFFE25A00) {
						tiles[xx + (yy * WIDTH)] = new FloorTile(xx*TILE_SIZE, yy*TILE_SIZE, Tile.TILE_WOODFLOOR);
					}else if(pixelAtual == 0xFF562200) {
						//Parede Madeira
						if(Game.rand.nextInt(100) < 33)
							tiles[xx + (yy * WIDTH)] = new WallTile(xx*TILE_SIZE, yy*TILE_SIZE, Tile.TILE_WOODENWALL1);
						else if(Game.rand.nextInt(100) < 66)
							tiles[xx + (yy * WIDTH)] = new WallTile(xx*TILE_SIZE, yy*TILE_SIZE, Tile.TILE_WOODENWALL2);
						else
							tiles[xx + (yy * WIDTH)] = new WallTile(xx*TILE_SIZE, yy*TILE_SIZE, Tile.TILE_WOODENWALL3);
					}else if(pixelAtual == 0xFF51AEFF) {
						//Água
						tiles[xx + (yy * WIDTH)] = new WallTile(xx*TILE_SIZE,yy*TILE_SIZE,Tile.TILE_WATER);
					}else if(pixelAtual == 0xFF0026FF) {
						//Player
						Game.player.setX(xx*16);
						Game.player.setY(yy*16);
					}else if(pixelAtual == 0xFFd77bba) {
						//NPC
					}else if(pixelAtual == 0xFFFF0000) {
						//Slime
						BufferedImage[] buf = new BufferedImage[3];
						buf[0] = Game.spritesheet.getSprite(112,0,16,16);
						buf[1] = Game.spritesheet.getSprite(128,0,16,16);
						buf[2] = Game.spritesheet.getSprite(144,0,16,16);
						Enemy en = new Enemy(xx*16,yy*16,16,16,buf);
						Game.entities.add(en);
						Game.enemies.add(en);
					}else if(pixelAtual == 0xFFFFD800) {
						//Espada
						Game.entities.add(new Axe(xx*TILE_SIZE,yy*TILE_SIZE,TILE_SIZE,TILE_SIZE,Entity.AXE_EN));
					}else if(pixelAtual == 0xFFFF00DC) {
						//Cura
						Heart pack = new Heart(xx*TILE_SIZE,yy*TILE_SIZE,TILE_SIZE,TILE_SIZE,Entity.HEART_EN);
						Game.entities.add(pack);
					}else if(pixelAtual == 0xFF4CFF00) {
						//Poção
						Game.entities.add(new Potion(xx*TILE_SIZE,yy*TILE_SIZE,TILE_SIZE,TILE_SIZE,Entity.POTION_EN));
					}else if(pixelAtual == 0xFF7F0037) {
						//Portal
						Game.entities.add(new Portal(xx*TILE_SIZE,yy*TILE_SIZE,TILE_SIZE,TILE_SIZE,Entity.PORTAL_EN));
					}else if(pixelAtual == 0xFFBC42FB) {
						//CheckPoint
						Game.entities.add(new CheckPoint(xx*TILE_SIZE,yy*TILE_SIZE,TILE_SIZE,TILE_SIZE,Entity.CHECKPOINT_EN));
					}else {
						tiles[xx + (yy * WIDTH)] = new FloorTile(xx*TILE_SIZE, yy*TILE_SIZE, Tile.TILE_BLANK);
					}
				}
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void RandomMap() {
		
		Game.player.setX(0);
		Game.player.setY(0);
		WIDTH = 100;
		HEIGHT = 100;
		tiles = new Tile[WIDTH * HEIGHT];
		
		for(int xx = 0; xx < WIDTH; xx++) {
			for(int yy = 0; yy < HEIGHT; yy++) {
				tiles[xx + (yy*WIDTH)] = new WallTile(xx*16,yy*16,Tile.TILE_STONEWALL);
			}
		}
		
		int dir = 0;
		int xx = 0, yy = 0;
		
		for(int i = 0; i < 200; i++) {
			
			tiles[xx + (yy*WIDTH)] = new FloorTile(xx*16,yy*16,Tile.TILE_GRASSFLOOR1);
			if(dir == 0) {
				//direita
				if(xx < WIDTH) {
					xx++;
				}
			}else if(dir == 1){
				//esquerda
				if(xx > 0) {
					xx--;
				}
			}else if(dir == 2){
				//baixo
				if(yy < HEIGHT) {
					yy++;
				}
			}else if(dir == 3){
				//cima
				if(yy > 0) {
					yy--;
				}
			}
			
			if(Game.rand.nextInt(100) < 30) {
				dir = Game.rand.nextInt(4);
			}
			
		}
	}
	
	public static void generateParticles(int amount, int x , int y) {
		for(int i = 0; i < amount; i++) {
			Game.entities.add(new Particle(x,y,1,1,null));
		}
	}
	
	public static boolean isFreeDynamic(int xnext, int ynext, int width, int height) {
		int x1 = xnext / TILE_SIZE;
		int y1 = ynext / TILE_SIZE;
		
		int x2 = (xnext+width-1) / TILE_SIZE;
		int y2 = ynext / TILE_SIZE;
		
		int x3 = xnext / TILE_SIZE;
		int y3 = (ynext+height-1) / TILE_SIZE;
		
		int x4 = (xnext+width-1) / TILE_SIZE;
		int y4 = (ynext+height-1) / TILE_SIZE;
		
		return !((tiles[x1 + (y1*World.WIDTH)] instanceof WallTile) ||
				 (tiles[x2 + (y2*World.WIDTH)] instanceof WallTile) ||
				 (tiles[x3 + (y3*World.WIDTH)] instanceof WallTile) ||
				 (tiles[x4 + (y4*World.WIDTH)] instanceof WallTile));
		
	}
	
	public static boolean isFree(int xnext, int ynext) {
		int x1 = xnext / TILE_SIZE;
		int y1 = ynext / TILE_SIZE;
		
		int x2 = (xnext+TILE_SIZE-1) / TILE_SIZE;
		int y2 = ynext / TILE_SIZE;
		
		int x3 = xnext / TILE_SIZE;
		int y3 = (ynext+TILE_SIZE-1) / TILE_SIZE;
		
		int x4 = (xnext+TILE_SIZE-1) / TILE_SIZE;
		int y4 = (ynext+TILE_SIZE-1) / TILE_SIZE;
		
		return !((tiles[x1 + (y1*World.WIDTH)] instanceof WallTile) ||
				 (tiles[x2 + (y2*World.WIDTH)] instanceof WallTile) ||
				 (tiles[x3 + (y3*World.WIDTH)] instanceof WallTile) ||
				 (tiles[x4 + (y4*World.WIDTH)] instanceof WallTile));
		
	}
	
	public static void restartGame(String level){
		Game.entities.clear();
		Game.enemies.clear();
		Game.slashs.clear();
		Game.entities = new ArrayList<Entity>();
		Game.enemies = new ArrayList<Enemy>();
		Game.spritesheet = new Spritesheet("/spritesheet.png");
		Game.player = new Player(0,0,16,32,Game.spritesheet.getSprite(32, 0, 16, 32));
		Game.entities.add(Game.player);
		Game.world = new World("/"+level);
		return;
	}
	
	public void render(Graphics g) {
		int xstart = Camera.x >> 4 ;
		int ystart = Camera.y >> 4;
		
		int xfinal = xstart + (Game.WIDTH >> 4);
		int yfinal = ystart + (Game.HEIGHT >> 4);
		
		for(int xx = xstart; xx <= xfinal; xx++) {
			for(int yy = ystart; yy <= yfinal; yy++) {
				if(xx < 0 || yy < 0 || xx >= WIDTH || yy >= HEIGHT) {
					continue;
				}
				Tile tile = tiles[xx + (yy*WIDTH)];
				tile.render(g);
			}
		}
	}
		
	public static void renderMiniMap() {
		for(int i = 0; i < Game.minimapaPixels.length; i++) {
			Game.minimapaPixels[i] = 0;
		}
		for(int xx = 0; xx < WIDTH; xx++) {
			for(int yy = 0; yy < HEIGHT; yy++) {
				if(tiles[xx + (yy*HEIGHT)] instanceof WallTile) {
					Game.minimapaPixels[xx + (yy*HEIGHT)] = 0xffffff;
				}
			}
		}
		
		int xPlayer = Game.player.getX()/16;
		int yPlayer = Game.player.getY()/16;
		
		Game.minimapaPixels[xPlayer + (yPlayer*HEIGHT)] = 0xff0000;

	}
	
}
