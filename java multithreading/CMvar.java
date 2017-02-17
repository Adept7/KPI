import java.util.Random;

public class CMvar {
	private Random random;
	
	private byte BYTE;
	private short SHORT;
	private int INT;
	private long LONG;
	private float FLOAT;
	private double DOUBLE;
	private char CHAR;
	private boolean BOOLEAN;	
	
	CMvar(){
		random = new Random();
		
		setByte();
		setShort();
		setInt();
		setLong();
		setFloat();
		setDouble();
		setChar();
		setBoolean();
	}
	
	public void setVar(int p_num){
		switch(p_num){
			case (1)://consumer
				getLong();
				getShort();
				getByte();
				getFloat();
				break;
			case (3)://producer
				setLong();
				setFloat();
				setDouble();
				setChar();
				break;
			case (4)://consumer
				getBoolean();
				getInt();
				getDouble();
				getChar();
				break;
			default:
		}
	}
	
	
	
	private void setByte(){
		BYTE = (byte) random.nextInt();
	}
	
	private void setShort(){
		SHORT = (short) random.nextInt();
	}
	
	private void setInt(){
		INT = random.nextInt();
	}
	
	private void setLong(){
		LONG = random.nextLong();
	}
	
	private void setFloat(){
		FLOAT = random.nextFloat();
	}
	
	private void setDouble(){
		DOUBLE = random.nextDouble();
	}
	
	private void setChar(){
		CHAR = (char) random.nextInt();
	}
	
	private void setBoolean(){
		BOOLEAN = random.nextBoolean();
	}
	
	
	
	private byte getByte(){
		return BYTE;
	}
	
	private short getShort(){
		return SHORT;
	}
	
	private int getInt(){
		return INT;
	}
	
	private long getLong(){
		return LONG;
	}
	
	private float getFloat(){
		return FLOAT;
	}
	
	private double getDouble(){
		return DOUBLE;
	}
	
	private char getChar(){
		return CHAR;
	}
	
	private boolean getBoolean(){
		return BOOLEAN;
	}
}
