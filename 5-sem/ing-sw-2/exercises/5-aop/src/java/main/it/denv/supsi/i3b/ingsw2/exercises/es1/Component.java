package it.denv.supsi.i3b.ingsw2.exercises.es1;

import java.util.ArrayList;

abstract class Component implements IAcceptor {
	private ArrayList<IAcceptor> components = new ArrayList<>();

	public void addChild(IAcceptor child){
		components.add(child);
	}
	public void removeChild(IAcceptor child){
		components.remove(child);
	}

	public ArrayList<IAcceptor> getChildren(){
		return components;
	}

	public IAcceptor getChild(int index){
		return components.get(index);
	}
}
