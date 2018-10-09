package it.denv.supsi.i3b.ingsw2.exercises.es1;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class SequenceCacheTest {

	@Test
	void length() {
		SequenceCache sq = new SequenceCache();
		assertEquals(6, sq.length(10));
	}
}