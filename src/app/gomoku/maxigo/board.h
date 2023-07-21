#ifndef BOARD_H
#define BOARD_H

//#ifdef X86
#include <cstdio>
#include <cstdint>
//#endif

#include <assert.h>

//#ifdef X86
//#define	min	std::min
//#define	max	std::max
//#endif
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

// Port of the JavaScript MaxiGo engine

#define STONE_BLACK 1
#define STONE_EMPTY 0
#define STONE_WHITE -1

#ifndef	BOARD_SIZE
#define	BOARD_SIZE	15
#endif

#define	TN	((threat_t) 0)
#define	TB3	((threat_t) 1)
#define	T3	((threat_t) 2)
#define	TS3	((threat_t) 3)
#define	T4	((threat_t) 4)
#define	TS4	((threat_t) 5)
#define	TWin	((threat_t) 6)

// MIN/MAX values safe under sign-swaps, -(2^31)+1, (2^31)-1
#define	VALUE_MIN	-2147483647
#define	VALUE_MAX	2147483647

#define	order_t		uint8_t
#define	score_t		int32_t
#define	threat_t	uint8_t
#define	pos_t		int8_t
#define	piece_t		int8_t
#define	lookup_t	uint16_t

order_t order(threat_t threat) {
	if (threat == TWin)
		return 5;
	if (threat >= T4)
		return 4;
	if (threat >= TB3)
		return 3;
	return 0;
}

const score_t threat_score[] = {
	0,	// TN
	100,	// TB3
	200,	// T3
	500,	// TS3
	1000,	// T4
	10000,	// TS4
	1000000,// TWin
};

score_t threat_to_score(threat_t threat) {
	return threat_score[threat];
}

#if 1
#include "threatstable24.h"

threat_t threats_lookup(lookup_t value, piece_t player) {
  assert(player == STONE_BLACK);  // Only use one lookup table

  uint16_t index = value >> 3;  // divide by 8 to get pack
  uint16_t pack_index = value & 0x7;  // index within pack

  // Get packed word
  uint16_t bi = index*3;  // byte_index, 3 bytes = 24 bits
//#ifdef X86
  uint8_t b0 = black_threats24[bi];
  uint8_t b1 = black_threats24[bi+1];
  uint8_t b2 = black_threats24[bi+2];
//#else
//  uint8_t b0 = pgm_read_byte(&black_threats24[bi]);
//  uint8_t b1 = pgm_read_byte(&black_threats24[bi+1]);
//  uint8_t b2 = pgm_read_byte(&black_threats24[bi+2]);
//#endif
  uint32_t packed = (((uint32_t) b0) << 16) | (((uint32_t) b1) << 8) | ((uint32_t) b2);
  packed >>= (pack_index*3);
  packed &= 0x7;

  return ((threat_t) packed);
}
#endif

//#if 1
//// Old 4+4-in-byte bit encoding version, uses too much space
//#include "threatstable.h"
//
//threat_t threats_lookup(lookup_t value, piece_t player) {
//	uint8_t threatbyte = 0;
//	if (player == STONE_BLACK) {
////#ifdef X86
//		threatbyte = black_threats[value >> 1];	// 4/4-bit packing
////#else
////    threatbyte = pgm_read_byte(&black_threats[value >> 1]);
////#endif
//	} else {
//		assert(false);
//		assert(player == STONE_WHITE);
//		//threatbyte = white_threats[value >> 1];	// 4/4-bit packing
//	}
//	if (value & 0x01 == 0x01)
//		threatbyte >>= 4;	// Upper 4 bits
//	threatbyte &= 0x0f;	// Only keep 4 bits
//
//	return ((threat_t) threatbyte);
//}
//#endif

typedef struct Move {
public:
	score_t	value;
	pos_t	y;
	pos_t	x;

	Move(score_t value, pos_t y, pos_t x) {
		this->value = value;
		this->y = y;
		this->x = x;
	}

	bool operator==(const Move& m1) const {
		return (value == m1.value && y == m1.y && x == m1.x);
	}
} move_t;

//#ifndef X86
//void displaySerial(const piece_t signMap[BOARD_SIZE][BOARD_SIZE]) {
//  Serial.println(F(""));
//  for (pos_t y = 0; y < BOARD_SIZE; ++y) {
//    for (pos_t x = 0; x < BOARD_SIZE; ++x) {
//      Serial.print(F(" "));
//      piece_t piece = signMap[y][x];
//      switch (piece) {
//        case STONE_BLACK:
//          Serial.print(F("X"));
//          break;
//        case STONE_WHITE:
//          Serial.print(F("O"));
//          break;
//        case STONE_EMPTY:
//          Serial.print(F("."));
//          break;
//        default:
//          Serial.print(F("?:"));
//          Serial.print(piece);
//          break;
//      }
//    }
//    Serial.println(F(""));
//  }
//  Serial.println(F(""));
//  Serial.println(F(""));
//  Serial.println(F(""));
//}
//#endif

class Board {
public:
	piece_t player;
	uint8_t free;
	pos_t	mid_x;
	pos_t	mid_y;
	piece_t signMap[BOARD_SIZE][BOARD_SIZE];

//#ifndef X86
//  void display(void) {
//    displaySerial(signMap);
//  }
//#endif

	void reset(void) {
		for (pos_t y = 0; y < BOARD_SIZE; ++y)
			for (pos_t x = 0; x < BOARD_SIZE; ++x)
				signMap[y][x] = STONE_EMPTY;

		player = STONE_BLACK;
		free = BOARD_SIZE*BOARD_SIZE;
		mid_x = BOARD_SIZE >> 1;
		mid_y = BOARD_SIZE >> 1;
	}

	bool is_in(pos_t y, pos_t x) const {
		return x >= 0 && y >= 0 && x < BOARD_SIZE && y < BOARD_SIZE;
	}
	piece_t get(pos_t y, pos_t x) const {
		assert(is_in(y, x));
		return signMap[y][x];
	}
  piece_t remove(pos_t y, pos_t x) {
    piece_t res = signMap[y][x];
    if (res != STONE_EMPTY) {
      free += 1;
      player = (player == STONE_BLACK) ? STONE_WHITE : STONE_BLACK;
    }
    signMap[y][x] = STONE_EMPTY;

    return res;
  }
	bool is_full() const { return free == 0; }
	void move(pos_t y, pos_t x, piece_t player) {
		assert(signMap[y][x] == STONE_EMPTY);
		signMap[y][x] = player;
		assert(free > 0);
		free -= 1;
	}
	void undo(pos_t y, pos_t x) {
		assert(signMap[y][x] != STONE_EMPTY);
		signMap[y][x] = STONE_EMPTY;
		free += 1;
	}

	/* Extract a 9-position line centered around (y,x) with one-step
	 * offsets (oy,ox), with oy, ox in {-1,0,1}.  Any piece outside the
	 * board received the value of outside_board_piece.
	 */
	lookup_t compute_lookup_value(pos_t y, pos_t x, pos_t oy, pos_t ox,
		piece_t outside_board_piece, bool flip)
	{
		lookup_t value = 0;
		for (pos_t i = -4; i <= 4; ++i) {
			pos_t ey = y + i * oy;
			pos_t ex = x + i * ox;
			piece_t piece = is_in(ey, ex) ? get(ey, ex) : outside_board_piece;
			if (flip)
				piece = -piece;
			value *= 3;
			value += piece + 1;
		}
		return value;
	}

	lookup_t compute_lookup_value_fixcenter(pos_t y, pos_t x, pos_t oy, pos_t ox,
		piece_t outside_board_piece, piece_t center_piece, bool flip) const
	{
		lookup_t value = 0;
		for (pos_t i = -4; i <= -1; ++i) {
			pos_t ey = y + i * oy;
			pos_t ex = x + i * ox;
			piece_t piece = is_in(ey, ex) ? get(ey, ex) : outside_board_piece;
			if (flip)
				piece = -piece;
			value *= 3;
			value += piece + 1;
		}
		value *= 3;
		if (flip)
			center_piece = -center_piece;
		value += center_piece + 1;
		for (pos_t i = 1; i <= 4; ++i) {
			pos_t ey = y + i * oy;
			pos_t ex = x + i * ox;
			piece_t piece = is_in(ey, ex) ? get(ey, ex) : outside_board_piece;
			if (flip)
				piece = -piece;
			value *= 3;
			value += piece + 1;
		}
		return value;
	}
	threat_t lookup_possible_threat_dir(pos_t y, pos_t x, pos_t oy, pos_t ox,
		piece_t outside_board_piece, piece_t threat_player) const
	{
		lookup_t value = compute_lookup_value_fixcenter(y, x, oy, ox,
			outside_board_piece, threat_player,
			threat_player == STONE_WHITE);

		return threats_lookup(value, STONE_BLACK);
	}

	// TODO: unroll the other ox/oy combinations, each saving a bit
	score_t threatscore_black_white_01(pos_t y, pos_t x) const {
		score_t score = 0;

		lookup_t value_black = 0;
		lookup_t value_white = 0;
		for (pos_t i = -4; i <= -1; ++i) {
			pos_t ey = y;
			pos_t ex = x + i;

			// Black:
			// 	outside_board_piece = -1
			// 	center_piece = 1
			// 	flip = false
			// White:
			// 	outside_board_piece = 1
			// 	center_piece = -1
			// 	flip = true
			value_black *= 3;
			value_white *= 3;
			if (is_in(ey, ex)) {
				piece_t piece = get(ey, ex);
				value_black += piece + 1;
				value_white += -piece + 1;
			} else {
				// Black: *3 + 0  (outside_board_piece = -1 and flip=false)
				// White: *3 + 0  (outside_board_piece = 1, but flip=true)
				// XXX: Nothing to do
			}
		}
		value_black *= 3;
		value_black += (STONE_BLACK + 1);
		value_white *= 3;
		value_white += (-STONE_WHITE + 1);	// Minus due to flip = true

		for (pos_t i = 1; i <= 4; ++i) {
			pos_t ey = y;
			pos_t ex = x + i;

			value_black *= 3;
			value_white *= 3;
			if (is_in(ey, ex)) {
				piece_t piece = get(ey, ex);
				value_black += piece + 1;
				value_white += -piece + 1;
			} else {
				// Black: *3 + 0  (outside_board_piece = -1 and flip=false)
				// White: *3 + 0  (outside_board_piece = 1, but flip=true)
				// XXX: Nothing to do
			}
		}

		score += threat_to_score(threats_lookup(value_black, STONE_BLACK));
		score -= threat_to_score(threats_lookup(value_white, STONE_BLACK));

		return score;
	}
	score_t threatscore_black_white_10(pos_t y, pos_t x) const
	{
		score_t score = 0;

		lookup_t value_black = 0;
		lookup_t value_white = 0;
		for (pos_t i = -4; i <= -1; ++i) {
			pos_t ey = y + i;
			pos_t ex = x;

			// Black:
			// 	outside_board_piece = -1
			// 	center_piece = 1
			// 	flip = false
			// White:
			// 	outside_board_piece = 1
			// 	center_piece = -1
			// 	flip = true
			value_black *= 3;
			value_white *= 3;
			if (is_in(ey, ex)) {
				piece_t piece = get(ey, ex);
				value_black += piece + 1;
				value_white += -piece + 1;
			} else {
				// Black: *3 + 0  (outside_board_piece = -1 and flip=false)
				// White: *3 + 0  (outside_board_piece = 1, but flip=true)
				// XXX: Nothing to do
			}
		}
		value_black *= 3;
		value_black += (STONE_BLACK + 1);
		value_white *= 3;
		value_white += (-STONE_WHITE + 1);	// Minus due to flip = true

		for (pos_t i = 1; i <= 4; ++i) {
			pos_t ey = y + i;
			pos_t ex = x;

			value_black *= 3;
			value_white *= 3;
			if (is_in(ey, ex)) {
				piece_t piece = get(ey, ex);
				value_black += piece + 1;
				value_white += -piece + 1;
			} else {
				// Black: *3 + 0  (outside_board_piece = -1 and flip=false)
				// White: *3 + 0  (outside_board_piece = 1, but flip=true)
				// XXX: Nothing to do
			}
		}

		score += threat_to_score(threats_lookup(value_black, STONE_BLACK));
		score -= threat_to_score(threats_lookup(value_white, STONE_BLACK));

		return score;
	}
	score_t threatscore_black_white_11(pos_t y, pos_t x) const {
		score_t score = 0;

		lookup_t value_black = 0;
		lookup_t value_white = 0;
		for (pos_t i = -4; i <= -1; ++i) {
			pos_t ey = y + i;
			pos_t ex = x + i;

			// Black:
			// 	outside_board_piece = -1
			// 	center_piece = 1
			// 	flip = false
			// White:
			// 	outside_board_piece = 1
			// 	center_piece = -1
			// 	flip = true
			value_black *= 3;
			value_white *= 3;
			if (is_in(ey, ex)) {
				piece_t piece = get(ey, ex);
				value_black += piece + 1;
				value_white += -piece + 1;
			} else {
				// Black: *3 + 0  (outside_board_piece = -1 and flip=false)
				// White: *3 + 0  (outside_board_piece = 1, but flip=true)
				// XXX: Nothing to do
			}
		}
		value_black *= 3;
		value_black += (STONE_BLACK + 1);
		value_white *= 3;
		value_white += (-STONE_WHITE + 1);	// Minus due to flip = true

		for (pos_t i = 1; i <= 4; ++i) {
			pos_t ey = y + i;
			pos_t ex = x + i;

			value_black *= 3;
			value_white *= 3;
			if (is_in(ey, ex)) {
				piece_t piece = get(ey, ex);
				value_black += piece + 1;
				value_white += -piece + 1;
			} else {
				// Black: *3 + 0  (outside_board_piece = -1 and flip=false)
				// White: *3 + 0  (outside_board_piece = 1, but flip=true)
				// XXX: Nothing to do
			}
		}

		score += threat_to_score(threats_lookup(value_black, STONE_BLACK));
		score -= threat_to_score(threats_lookup(value_white, STONE_BLACK));

		return score;
	}
	score_t threatscore_black_white_1m1(pos_t y, pos_t x) const {
		score_t score = 0;

		lookup_t value_black = 0;
		lookup_t value_white = 0;
		for (pos_t i = -4; i <= -1; ++i) {
			pos_t ey = y + i;
			pos_t ex = x - i;

			// Black:
			// 	outside_board_piece = -1
			// 	center_piece = 1
			// 	flip = false
			// White:
			// 	outside_board_piece = 1
			// 	center_piece = -1
			// 	flip = true
			value_black *= 3;
			value_white *= 3;
			if (is_in(ey, ex)) {
				piece_t piece = get(ey, ex);
				value_black += piece + 1;
				value_white += -piece + 1;
			} else {
				// Black: *3 + 0  (outside_board_piece = -1 and flip=false)
				// White: *3 + 0  (outside_board_piece = 1, but flip=true)
				// XXX: Nothing to do
			}
		}
		value_black *= 3;
		value_black += (STONE_BLACK + 1);
		value_white *= 3;
		value_white += (-STONE_WHITE + 1);	// Minus due to flip = true

		for (pos_t i = 1; i <= 4; ++i) {
			pos_t ey = y + i;
			pos_t ex = x - i;

			value_black *= 3;
			value_white *= 3;
			if (is_in(ey, ex)) {
				piece_t piece = get(ey, ex);
				value_black += piece + 1;
				value_white += -piece + 1;
			} else {
				// Black: *3 + 0  (outside_board_piece = -1 and flip=false)
				// White: *3 + 0  (outside_board_piece = 1, but flip=true)
				// XXX: Nothing to do
			}
		}

		score += threat_to_score(threats_lookup(value_black, STONE_BLACK));
		score -= threat_to_score(threats_lookup(value_white, STONE_BLACK));

		return score;
	}

	score_t threatscore_black_white(
		pos_t y, pos_t x, pos_t oy, pos_t ox) const
	{
		score_t score = 0;

		lookup_t value_black = 0;
		lookup_t value_white = 0;
		for (pos_t i = -4; i <= -1; ++i) {
			pos_t ey = y + i * oy;
			pos_t ex = x + i * ox;

			// Black:
			// 	outside_board_piece = -1
			// 	center_piece = 1
			// 	flip = false
			// White:
			// 	outside_board_piece = 1
			// 	center_piece = -1
			// 	flip = true
			value_black *= 3;
			value_white *= 3;
			if (is_in(ey, ex)) {
				piece_t piece = get(ey, ex);
				value_black += piece + 1;
				value_white += -piece + 1;
			} else {
				// Black: *3 + 0  (outside_board_piece = -1 and flip=false)
				// White: *3 + 0  (outside_board_piece = 1, but flip=true)
				// XXX: Nothing to do
			}
		}
		value_black *= 3;
		value_black += (STONE_BLACK + 1);
		value_white *= 3;
		value_white += (-STONE_WHITE + 1);	// Minus due to flip = true

		for (pos_t i = 1; i <= 4; ++i) {
			pos_t ey = y + i * oy;
			pos_t ex = x + i * ox;

			value_black *= 3;
			value_white *= 3;
			if (is_in(ey, ex)) {
				piece_t piece = get(ey, ex);
				value_black += piece + 1;
				value_white += -piece + 1;
			} else {
				// Black: *3 + 0  (outside_board_piece = -1 and flip=false)
				// White: *3 + 0  (outside_board_piece = 1, but flip=true)
				// XXX: Nothing to do
			}
		}

		score += threat_to_score(threats_lookup(value_black, STONE_BLACK));
		score -= threat_to_score(threats_lookup(value_white, STONE_BLACK));

		return score;
	}

	threat_t lookup_possible_threat(pos_t y, pos_t x,
		piece_t outside_board_piece, piece_t threat_player) const
	{
		threat_t maxt = TN;
		maxt = max(maxt, lookup_possible_threat_dir(
			y, x, 0, 1, outside_board_piece, threat_player));
		maxt = max(maxt, lookup_possible_threat_dir(
			y, x, 1, 0, outside_board_piece, threat_player));
		maxt = max(maxt, lookup_possible_threat_dir(
			y, x, 1, 1, outside_board_piece, threat_player));
		maxt = max(maxt, lookup_possible_threat_dir(
			y, x, 1, -1, outside_board_piece, threat_player));
		return maxt;
	}

	threat_t lookup_threat(pos_t y, pos_t x, pos_t oy, pos_t ox,
		piece_t outside_board_piece, piece_t threat_player)
	{
		lookup_t value = compute_lookup_value(y, x, oy, ox,
			outside_board_piece, threat_player == STONE_WHITE);

		return threats_lookup(value, STONE_BLACK);
	}

	// Winning move at (y,x)?
	bool winner_at(pos_t y, pos_t x) {
		piece_t player = get(y, x);
		threat_t maxt = highest_existing_threat_at(y, x, player);
		return maxt == TWin;
	}

	// Heuristic evaluation function used in Minimax
	score_t heuristic_evaluation_fast(void) {
		score_t score = 0;
		for (pos_t y = 0; y < BOARD_SIZE; ++y) {
			for (pos_t x = 0; x < BOARD_SIZE; ++x) {
				if (get(y, x) != STONE_EMPTY)
					continue;

				// Black and white
				score += threatscore_black_white_01(y, x);
				// Equal to:
				// score += threat_to_score(
				//	lookup_possible_threat_dir(y, x, 0, 1, -1, 1));
				// score -= threat_to_score(
				//	lookup_possible_threat_dir(y, x, 0, 1, 1, -1));

				score += threatscore_black_white_10(y, x);
				score += threatscore_black_white_11(y, x);
				score += threatscore_black_white_1m1(y, x);
			}
		}
		return score;
	}

	// Heuristic evaluation function using in Minimax
	score_t heuristic_evaluation(void) {
		score_t score = 0;
		for (pos_t y = 0; y < BOARD_SIZE; ++y) {
			for (pos_t x = 0; x < BOARD_SIZE; ++x) {
				if (get(y, x) != STONE_EMPTY)
					continue;

				// Black
				score += threat_to_score(
					lookup_possible_threat_dir(y, x, 0, 1, -1, 1));
				score += threat_to_score(
					lookup_possible_threat_dir(y, x, 1, 0, -1, 1));
				score += threat_to_score(
					lookup_possible_threat_dir(y, x, 1, 1, -1, 1));
				score += threat_to_score(
					lookup_possible_threat_dir(y, x, 1, -1, -1, 1));

				// White
				score -= threat_to_score(
					lookup_possible_threat_dir(y, x, 0, 1, 1, -1));
				score -= threat_to_score(
					lookup_possible_threat_dir(y, x, 1, 0, 1, -1));
				score -= threat_to_score(
					lookup_possible_threat_dir(y, x, 1, 1, 1, -1));
				score -= threat_to_score(
					lookup_possible_threat_dir(y, x, 1, -1, 1, -1));
			}
		}
		return score;
	}

	threat_t highest_existing_threat_at(pos_t y, pos_t x, piece_t player) {
		threat_t maxt = TN;
		maxt = max(maxt, lookup_threat(y, x, 0, 1, -player, player));
		maxt = max(maxt, lookup_threat(y, x, 1, 0, -player, player));
		maxt = max(maxt, lookup_threat(y, x, 1, 1, -player, player));
		maxt = max(maxt, lookup_threat(y, x, 1, -1, -player, player));
		return maxt;
	}

	Board(void) {
		reset();
	}

	Board(
		const piece_t startingSignMap[][BOARD_SIZE],	// [y][x]
		piece_t player
	) {
		reset();

		this->player = player;
		for (pos_t y = 0; y < BOARD_SIZE; ++y) {
			for (pos_t x = 0; x < BOARD_SIZE; ++x) {
				piece_t piece = startingSignMap[y][x];
				signMap[y][x] = piece;
				if (piece != STONE_EMPTY)
					this->free -= 1;
			}
		}
	}

	threat_t highest_existing_threat(piece_t player) {
		threat_t maxt = TN;
		for (pos_t y = 0; y < BOARD_SIZE; ++y) {
			for (pos_t x = 0; x < BOARD_SIZE; ++x) {
				piece_t piece = get(y, x);
				if (piece != player)
					continue;

				maxt = max(maxt, highest_existing_threat_at(y, x, player));
			}
		}
		return maxt;
	}

	bool has_nearby(pos_t y, pos_t x, pos_t radius) const {
		pos_t min_y = max(0, y - radius);
		pos_t max_y = min(BOARD_SIZE-1, y + radius);
		pos_t min_x = max(0, x - radius);
		pos_t max_x = min(BOARD_SIZE-1, x + radius);
		for (pos_t ny = min_y; ny <= max_y; ++ny) {
			for (pos_t nx = min_x; nx <= max_x; ++nx) {
				if (get(ny, nx) != STONE_EMPTY)
					return true;
			}
		}
		return false;
	}

//#ifndef X86
//	move_t baby_ai(void) const {
//		move_t chosen_move(0, 0, 0);
//
//		// No move left
//		if (is_full()) { return chosen_move; }
//
//		int moves_considered = 0;
//		for (pos_t y = 0; y < BOARD_SIZE; ++y) {
//			for (pos_t x = 0; x < BOARD_SIZE; ++x) {
//				if (get(y, x) != STONE_EMPTY)
//					continue;   // skip: position taken
//
//				// Only consider moves in the vicinity of placed stones
//				if (!has_nearby(y, x, 1))
//					continue;
//
//				// Reservoir-sample uniform, see
//				// https://en.m.wikipedia.org/wiki/Reservoir_sampling
//				move_t candidate(0, y, x);
//				if (moves_considered <= 1) {
//					chosen_move = candidate;
//				} else {
//					int j = random(1, moves_considered+2);
//					if (j <= 1)
//						chosen_move = candidate;
//				}
//				moves_considered += 1;
//			}
//		}
//		return chosen_move;
//	}
//#endif

	move_t negamax(int8_t depth, piece_t player) {
		return negamax_r(depth, VALUE_MIN, VALUE_MAX, player);
	}

	move_t negamax_r(int8_t depth, int32_t alpha, int32_t beta, piece_t player) {
#ifdef DEBUG
		printf("  negamax_r(depth=%d, alpha=%d, beta=%d, player=%d)\n",
			depth, alpha, beta, player);
#endif

		// Wins are handled in recursion, so the only terminal nodes
		// reached here are by draws.
		if (is_full()) { return move_t(0, 0, 0); }

		// Search budget exceeded => heuristic evaluation
		if (depth == 0) { return move_t(player*heuristic_evaluation_fast(), 0, 0); }

		order_t ostar_opp = order(highest_existing_threat(-player));
		order_t ostar = order(highest_existing_threat(player));

		score_t best_value = VALUE_MIN;
		pos_t best_y = 0;
		pos_t best_x = 0;

		for (pos_t y = 0; y < BOARD_SIZE; ++y) {
			for (pos_t x = 0; x < BOARD_SIZE; ++x) {
				// Only consider empty pieces.
				if (get(y, x) != STONE_EMPTY)
					continue;

				bool consider_move = false;
				if (ostar_opp > order(TN)) {
					// There is an opponent threat, two options:
					//  1. Own threat better than opponent threat => consider
					//  2. Own move lowers opponent threat
					threat_t possible_threat = lookup_possible_threat(
						y, x, -player, player);
					order_t possible_order = order(possible_threat);
					if (possible_order > ostar_opp) {
						consider_move = true;
					} else {
						// Our own attack not possible
						// here against open opponent
						// threat.  But, would opponent
						// move here increase highest
						// open threat?
						order_t ostar_opp_yx = order(
							lookup_possible_threat(y, x, player, -player));
						if (ostar_opp_yx > ostar_opp) {
							// (y,x) is actively
							// involved in the
							// current highest
							// opponent threat
							consider_move = true;
						}
					}
				} else {
					// No opponent threat open, use simple
					// nearby heuristic for now
					if (y == mid_y && x == mid_x) {
						consider_move = true;
					} else if (has_nearby(y, x, 1)) {
						consider_move = true;
					}
				}

				if (!consider_move)
					continue;

				// Make move
				move(y, x, player);
				score_t value_child = 0;
				if (winner_at(y, x)) {
					// Winning move just played, no need to
					// recurse
					value_child = 100000000;
				} else {
					// Recurse
#ifdef DEBUG
					printf("  %d recurse at (y,x)=(%d,%d)\n", depth, y, x);
#endif
					move_t best_r = negamax_r(depth-1, -beta, -alpha, -player);
					value_child = -best_r.value;
#ifdef DEBUG
					printf("  <-- to %d at (y,x)=(%d,%d), value_child=%d\n", depth, y, x, value_child);
#endif
				}
				undo(y, x);

				if (value_child > best_value) {
					best_value = value_child;
					best_y = y;
					best_x = x;
				}
				alpha = max(alpha, value_child);
				if (alpha >= beta) {
#ifdef DEBUG
					printf("  alpha >= beta (%d >= %d), returning\n", alpha, beta);
#endif
					return move_t(alpha, best_y, best_x);
				}
			}
		}
		return move_t(best_value, best_y, best_x);
	}
};

#endif
