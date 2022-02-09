package com.mygdx.game01;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.math.Rectangle;

public class RedDrop {

    public Texture redDrop;
    public Rectangle position;

    public RedDrop(){
        redDrop = new Texture(Gdx.files.internal("redDrop.png"));
        position = new Rectangle(64,480,64,64);
    }

    public void tick(){
        position.y-=200 * Gdx.graphics.getDeltaTime();
    }

    public void render(SpriteBatch batch){
        batch.draw(redDrop, position.x, position.y);
    }
}
