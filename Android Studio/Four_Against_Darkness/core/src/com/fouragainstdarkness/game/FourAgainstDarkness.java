package com.fouragainstdarkness.game;

import java.util.Iterator;
import java.util.Timer;

import com.badlogic.gdx.Application;
import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input.Keys;
import com.badlogic.gdx.audio.Music;
import com.badlogic.gdx.audio.Sound;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.g2d.TextureAtlas;
import com.badlogic.gdx.math.MathUtils;
import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.math.Vector3;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.InputListener;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.Button;
import com.badlogic.gdx.scenes.scene2d.ui.Image;
import com.badlogic.gdx.scenes.scene2d.ui.Skin;
import com.badlogic.gdx.scenes.scene2d.ui.Table;
import com.badlogic.gdx.scenes.scene2d.ui.TextButton;
import com.badlogic.gdx.utils.Array;
import com.badlogic.gdx.utils.ScreenUtils;
import com.badlogic.gdx.utils.TimeUtils;
import com.sun.org.apache.bcel.internal.generic.SWAP;

public class FourAgainstDarkness extends ApplicationAdapter {
	private Texture dropImage;
	private Texture bucketImage;
	private Texture buttonImage;
	private Texture entranceImage;
	private Sound dropSound;
	private Music rainMusic;
	private SpriteBatch batch;
	private OrthographicCamera camera;
	private Rectangle bucket;
	private Rectangle button;
	private Array<Rectangle> raindrops;
	private long lastDropTime;

	private Stage stage;
	private Table table;

	private int pontos=0;
	public BitmapFont font;
	public boolean choosenEntrance = false;
	public boolean choosenRoom = false;
	TextureAtlas entrancesSprites;
	TextureAtlas roomsSprites;
	Sprite entranceSprite,roomSprite;

	@Override
	public void create() {

		stage = new Stage();
		Gdx.input.setInputProcessor(stage);

		table = new Table();
		table.setFillParent(true);
		stage.addActor(table);

		table.setDebug(true); // This is optional, but enables debug lines for tables.

		// Add widgets to the table here.

		font = new BitmapFont();
		// load the images for the droplet and the bucket, 64x64 pixels each
		buttonImage = new Texture(Gdx.files.internal("button.png"));
		dropImage = new Texture(Gdx.files.internal("drop.png"));
		bucketImage = new Texture(Gdx.files.internal("bucket.png"));
		entrancesSprites = new TextureAtlas("entrances_sprites.txt");
		roomsSprites = new TextureAtlas("room_sprites.txt");

		// load the drop sound effect and the rain background "music"
		//dropSound = Gdx.audio.newSound(Gdx.files.internal("drop.wav"));
		//rainMusic = Gdx.audio.newMusic(Gdx.files.internal("rain.mp3"));

		if(Gdx.app.getType().equals(Application.ApplicationType.Desktop)) {
			Gdx.graphics.setWindowedMode(428, 926);
			//System.out.println("Desktop");
		}

		// start the playback of the background music immediately
		//rainMusic.setLooping(true);
		//rainMusic.play();

		// create the camera and the SpriteBatch
		camera = new OrthographicCamera();
		camera.setToOrtho(false, 428, 926);
		batch = new SpriteBatch();

		// create a Rectangle to logically represent the bucket
		bucket = new Rectangle();
		bucket.x = 428 / 2 - 64 / 2; // center the bucket horizontally
		bucket.y = 20; // bottom left corner of the bucket is 20 pixels above the bottom screen edge
		bucket.width = 64;
		bucket.height = 64;

		button = new Rectangle();
		button.x = 428 / 2 - 168 / 2; // center the bucket horizontally
		button.y = 926 / 2 - 60 / 2;; // bottom left corner of the bucket is 20 pixels above the bottom screen edge
		button.width = 168;
		button.height = 60;

		// create the raindrops array and spawn the first raindrop
		raindrops = new Array<Rectangle>();
		spawnRaindrop();
	}

	public void resize (int width, int height) {
		stage.getViewport().update(width, height, true);
	}

	private void spawnRaindrop() {
		Rectangle raindrop = new Rectangle();
		raindrop.x = MathUtils.random(0, 428-64);
		raindrop.y = 926;
		raindrop.width = 64;
		raindrop.height = 64;
		raindrops.add(raindrop);
		lastDropTime = TimeUtils.nanoTime();
	}

	public int D6(){
		int d6;
		d6 = MathUtils.random(1, 6);
		//System.out.println(d6);
		return d6;
	}

	public void Entrance(int d6){
	    switch(d6){
            case 1:
				entranceSprite = entrancesSprites.createSprite(String.valueOf(d6));
				choosenEntrance = true;
				break;
            case 2:
				entranceSprite = entrancesSprites.createSprite(String.valueOf(d6));
				choosenEntrance = true;
				break;
            case 3:
				entranceSprite = entrancesSprites.createSprite(String.valueOf(d6));
				choosenEntrance = true;
				break;
            case 4:
				entranceSprite = entrancesSprites.createSprite(String.valueOf(d6));
				choosenEntrance = true;
				break;
            case 5:
				entranceSprite = entrancesSprites.createSprite(String.valueOf(d6));
				choosenEntrance = true;
				break;
            case 6:
				entranceSprite = entrancesSprites.createSprite(String.valueOf(d6));
				choosenEntrance = true;
				break;
            default:
				choosenEntrance = false;
				break;
        }
    }

    public void Room(int d16, int d26){
		String choice = String.valueOf(d16) + String.valueOf(d26);
		switch(choice){
			case "11":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "12":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "13":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "14":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "15":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "16":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "21":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "22":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "23":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "24":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "25":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "26":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "31":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "32":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "33":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "34":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "35":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "36":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "41":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "42":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "43":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "44":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "45":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "46":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "51":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "52":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "53":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "54":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "55":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "56":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "61":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "62":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "63":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "64":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "65":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			case "66":
				roomSprite = roomsSprites.createSprite(choice);
				choosenRoom = true;
				break;
			default:
				choosenRoom = false;
				break;
		}
	}

	public String RoomContentsTable(int d16, int d26){
		int sd6 = d16 + d26;
		switch(sd6){
			case 2:
				return "Treasure found: roll on the Treasure table.";
			case 3:
				return "Treasure protected by a trap. Roll on the Traps table and on the Treasure table.";
			case 4:
				return "If corridor, empty. Otherwise, roll on the Special Events table.";
			case 5:
				return "Empty, but roll on the Special Feature table";
			case 6:
				return "Roll on the Vermin table.";
			case 7:
				return "Roll on the Minions table";
			case 8:
				return "If corridor, empty. Otherwise, roll on the Minions table.";
			case 9:
				return "Empty.";
			case 10:
				return "If corridor, empty. Otherwise, roll on Weird Monsters table.";
			case 11:
				return "Roll on the Boss table. Then roll d6. Add +1 for every boss or weird monster " +
						"that you have encountered so far in the game. if your total is " +
						"6+, or if the dungeon layout is complete, this is the final boss.";
			case 12:
				return "Empty if corridor. Otherwise, the room is a small dragon’s lair (see the " +
						"Boss table for dragon rules). The small dragon counts as a boss and " +
						"may be the final boss.";
			default:
				return "Error!";
		}
	}

	public String SpecialFeatureTable(int d6){
	    switch(d6) {
            case 1:
                return "Fountain: All wounded characters recover 1 Life the first time they " +
                        "encounter a fountain in an adventure. Further fountains have no effect.";
            case 2:
                return "Blessed Temple: A character of your choice gains a +1 on Attack " +
                        "against undead monsters or demons. As soon as the character kills at " +
                        "least one undead or demon, the bonus is gone.";
            case 3:
                return "Armory: All characters can change their weapons if they want, within " +
                        "the limits of the weapons allowed to their character type. For example, " +
                        "a Warrior who was using a sword and shield may discard his shield and " +
                        "take a two-handed weapon, or exchange his sword for a mace.";
            case 4:
                return "Cursed Altar: As you enter the room, an eerie glow emanates from a " +
                        "sinister altar. A random character is cursed and has now -1 on his " +
                        "Defense rolls. To break the curse, the character must either slay a boss " +
                        "monster alone, or enter a Blessed Temple (see 2, above), or have a " +
                        "Blessing spell cast on himself by a cleric.";
            case 5:
                return "Statue: you may leave the statue alone or touch it. If you touch it, roll " +
                        "d6. On a 1–3, the statue awakens and attacks your party (level 4 boss " +
                        "with 6 life points, immune to all spells; if you defeat it, you find 3d6 x 10 " +
                        "gold pieces inside). On a 4-6, the statue breaks, and you find 3d6 x 10 " +
                        "gold pieces inside.";
            case 6:
                return "Puzzle Room: the room contains a puzzle box. Its level is d6. You may " +
                        "leave it alone or try to solve it. For every failed attempt, the character " +
                        "trying to solve it loses 1 life. Wizards and rogues add their level to their " +
                        "puzzle-solving roll. If the puzzle is solved, the box opens: make a " +
                        "Treasure roll to determine its contents.";
            default:
                return "Error!";
        }
    }

    public String SpecialEventsTable(int d6){
	    switch(d6){
            case 1:
                return "A ghost passes through the party. All characters must save versus level " +
                        "4 fear or lose 1 life. A cleric adds his level to this roll.";
            case 2:
                return "Wandering monsters attack the party. Roll d6: 1-3 roll on the vermin " +
                        "table, 4 roll on the minions table, 5 roll on the weird monsters table, 6 " +
                        "roll on the boss table. Reroll any small dragons. A boss monster met as " +
                        "a wandering monster has no chance of being the final boss.";
            case 3:
                return "A lady in white appears and asks the party to complete a quest. If you " +
                        "accept, roll on the Quest table. If you refuse, she disappears. Ignore any " +
                        "further appearances of the Lady in White in the game.";
            case 4:
                return "Trap! Roll on the traps table.";
            case 5:
                return "You meet a wandering healer. He will heal your party at the cost of 10 " +
                        "gold pieces per life healed. You may heal as many life points as you can " +
                        "afford. You can meet the healer only once per game. If you meet him " +
                        "again, reroll this result.";
            case 6:
                return "You meet a wandering alchemist. He will sell you up to one potion of " +
                        "healing per party member (50 gold pieces each) or a single dose of " +
                        "blade poison (30 gold pieces). The potion of healing will heal all lost life " +
                        "points to a single character, and can be swallowed at any moment " +
                        "during the game as a free action. The blade poison lets you envenom a " +
                        "single arrow or slashing weapon (not a crushing weapon). That weapon " +
                        "will have a +1 on Attack against the first enemy you fight. Poison will not " +
                        "work on undead monsters, demons, blobs, automatons, or living " +
                        "statues.\n" +
                        "You can meet a wandering alchemist only once per game. If you meet " +
                        "him again, treat this result as a trap.";
            default:
                return "Error!";
        }
    }

    public String TreasureTable(int d6) {
        switch (d6){
            case 0:
                return "No treasure found";
            case 1:
                return "d6 gold pieces";
            case 2:
                return "2d6 gold pieces";
            case 3:
                return "A scroll with a random spell";
            case 4:
                return "One gem worth 2d6 x 5 gold pieces";
            case 5:
                return "One item of jewelry worth 3d6 x 10 gold pieces";
            case 6:
                return "One random magic item from the Magic Treasure table below.";
            default:
                return "Error!";
        }
    }

    public String MagicTreasureTable(int d6){
		switch (d6){
			case 1:
				return "Wand of Sleep: allows user to cast Sleep spell 3 times before its " +
						"energy is depleted. Only wizards and elves may use it. Add the user’s " +
						"level to determine the spell roll, as you would do for a Sleep spell cast " +
						"by that character.";
			case 2:
				return "Ring of Teleportation: allows user to automatically pass a Defense " +
						"roll by moving that character out of the room. That character may not " +
						"take part in the current combat, but rejoins the party as soon as the " +
						"combat is over. After one use, the ring loses its powers and becomes " +
						"a simple golden ring worth 1d6+1 gold pieces.";
			case 3:
				return "Fools Gold. These magical (but fake) gold pieces will let the user " +
						"automatically bribe the next monster that asks for a bribe. No matter " +
						"what the monster asks, the gold will appear enough to satisfy his " +
						"greed. This is a one-use magic item.";
			case 4:
				return "Magic Weapon. Gives +1 to its user’s Attack rolls. This is a permanent " +
						"magic item. Roll d6 to determine its type: 1 crushing light hand " +
						"weapon, 2 slashing light hand weapon, 3 crushing hand weapon, 4-5 " +
						"slashing hand weapon, 6 bow.";
			case 5:
				return "Potion of Healing: Can be swallowed at any moment, healing all lost " +
						"life to a single character. This does not require an action. This is a " +
						"one-use magic item, usable by all classes except barbarians.";
			case 6:
				return "Fireball Staff: This staff allows its user to cast Fireball spell twice, " +
						"then its powers are depleted. Only wizards may use it. Add the user’s " +
						"level to determine the spell roll, as you would do for a Fireball spell " +
						"cast by that character.";
			default:
				return "Error!";
		}
	}

	public String VerminTable(int d6){
		switch (d6){
			case 1:
				return "3d6 rats Level 1, no treasure. Any character wounded has a 1 in 6 " +
						"chance of losing 1 additional life due to an infected wound.\n" +
						"Reactions (d6): 1–3 flee, 4–6 fight";
			case 2:
				return "3d6 vampire bats, level 1, no treasure. Spells are cast at -1 due to " +
						"their distracting shrieking.\n" +
						"Reactions (d6): 1–3 flee, 4–6 fight";
			case 3:
				return "2d6 goblin swarmlings, level 3, treasure -1, morale -1 " +
						"Reactions (d6): 1 flee, 2-3 flee if outnumbered, 4 bribe (5 gp x goblin),\n" +
						"5–6 fight.";
			case 4:
				return "D6 giant centipedes, level 3, no treasure. Any character wounded " +
						"by a giant centipede must save versus level 2 poison or lose 1 " +
						"additional life.\n" +
						"Reactions (d6): 1 flee, 2-3 flee if outnumbered, 4-6 fight.";
			case 5:
				return "D6 vampire frogs, level 4, treasure -1.\n" +
						"Reactions (d6): 1 flee, 2-4 fight, 5-6 fight to the death";
			case 6:
				return "2d6 skeletal rats, level 3 undead, no treasure. Crushing weapon " +
						"attacks are at +1 against skeletal rats, but they cannot be attacked " +
						"by bows and slings.\n" +
						"Reactions (d6): 1-2 flee, 3-6 fight";
			default:
				return "Error!";
		}
	}

	@Override
	public void render() {

		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);
		stage.act(Gdx.graphics.getDeltaTime());
		stage.draw();
		if(!choosenEntrance){
			Entrance(D6());
			Image image1 = new Image(entranceSprite);
			//image1.setSize(100,100);
			image1.setPosition(300,300);
			stage.addActor(image1);
		}

		Skin neonSkin = new Skin(Gdx.files.internal("skin/neon-ui.json"));
		Button button2 = new TextButton("Botao 1", neonSkin,"default");
		button2.setSize(200,50);
		button2.setPosition(50,100);
		stage.addActor(button2);

		/*
		// clear the screen with a dark blue color. The
		// arguments to clear are the red, green
		// blue and alpha component in the range [0,1]
		// of the color to be used to clear the screen.
		ScreenUtils.clear(0, 0, 0, 1);

		// tell the camera to update its matrices.
		camera.update();

		// tell the SpriteBatch to render in the
		// coordinate system specified by the camera.
		batch.setProjectionMatrix(camera.combined);

		// begin a new batch and draw the bucket and
		// all drops
		batch.begin();
		font.draw(batch, String.valueOf(pontos), 390, 900);
		batch.draw(bucketImage, bucket.x, bucket.y);
		batch.draw(buttonImage, button.x, button.y);
		if(!choosenEntrance){
			int d6 = D6();
			Entrance(d6);
		}
		entranceSprite.setPosition(150, 600);
		entranceSprite.draw(batch);
		if(!choosenRoom){
			int d16 = D6();
			int d26 = D6();
			Room(d16,d26);
		}
		roomSprite.setPosition(150, 300);
		roomSprite.draw(batch);
		for(Rectangle raindrop: raindrops) {
			batch.draw(dropImage, raindrop.x, raindrop.y);
		}
		batch.end();
		tick();
		*/
	}

	public void tick(){
		/*
		Gdx.graphics.setTitle("Four Against Darkness - Score: "+pontos);
		// process user input
		if(Gdx.input.isTouched()) {
			Vector3 touchPos = new Vector3();
			touchPos.set(Gdx.input.getX(), Gdx.input.getY(), 0);
			camera.unproject(touchPos);
			bucket.x = touchPos.x - 64 / 2;
		}
		if(Gdx.input.isKeyPressed(Keys.LEFT)) bucket.x -= 200 * Gdx.graphics.getDeltaTime();
		if(Gdx.input.isKeyPressed(Keys.RIGHT)) bucket.x += 200 * Gdx.graphics.getDeltaTime();

		// make sure the bucket stays within the screen bounds
		if(bucket.x < 0) bucket.x = 0;
		if(bucket.x > 428 - 64) bucket.x = 428 - 64;

		// check if we need to create a new raindrop
		if(TimeUtils.nanoTime() - lastDropTime > 1000000000) spawnRaindrop();

		// move the raindrops, remove any that are beneath the bottom edge of
		// the screen or that hit the bucket. In the latter case we play back
		// a sound effect as well.
		for (Iterator<Rectangle> iter = raindrops.iterator(); iter.hasNext(); ) {
			Rectangle raindrop = iter.next();
			raindrop.y -= 200 * Gdx.graphics.getDeltaTime();
			if(raindrop.y + 64 < 0) iter.remove();
			if(raindrop.overlaps(bucket)) {
				pontos+=100;
				dropSound.play();
				iter.remove();
			}
		}

		 */

	}

	@Override
	public void dispose() {
		stage.dispose();

		/*
		// dispose of all the native resources
		entrancesSprites.dispose();
		roomsSprites.dispose();
		dropImage.dispose();
		bucketImage.dispose();
		dropSound.dispose();
		rainMusic.dispose();
		batch.dispose();
		 */
	}
}