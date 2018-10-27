package command;

public class Move implements Command {

	public Coordenate_States state;
	
	public int initial_coordenate, final_coordenate;

	public long time;
		
	
	public Move(int initial_coordenate, long time) {
		super();
		this.initial_coordenate = initial_coordenate;
		this.time = time;
	}


	@Override
	public String generateInstruction() {
		return initial_coordenate + ","+ time;
	}
	
}
