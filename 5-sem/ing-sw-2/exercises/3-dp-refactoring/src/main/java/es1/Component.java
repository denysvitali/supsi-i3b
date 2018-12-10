package es1;

import java.util.ArrayList;

abstract class Component implements IComposite {
	private ArrayList<IComposite> components = new ArrayList<>();

	public void addChild(IComposite child){
		components.add(child);
	}
	public void removeChild(IComposite child){
		components.remove(child);
	}

	public ArrayList<IComposite> getChildren(){
		return components;
	}

	public IComposite getChild(int index){
		return components.get(index);
	}
}
