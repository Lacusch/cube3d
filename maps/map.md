# Map rules

- The map **must** be composed of only 6 possible characters:
  - 0 for an empty space,
  - 1 for a wall,
  - N, S, E or W for the player’s start position and spawning
orientation.
- The map **must** be closed/surrounded by walls.
- Each type of element *can* be separated by one more empty line(s).
- Except for the map content (which always has to be the **last**), each type of element can be set in any order in the file.
- Each type of information from an element can be separated
by one or more space(s).
- The map must be parsed as it looks in the file. **Spaces are a valid part** of the
map and are up to you to handle.

## Parcing order

1. Parce all the elements (with `gnl`) exept the map.
2. If you find a Number before all the elements are filled, thrown an error.
3. Check if the map is closed or not

- [x] check for dublicates (in meta)
- [x] scan the map
- [x] fill the empty space with some recognisable `char` (-1)
- [x] check if The map has only valid characters
- [x] check for no and duplicate player
- [ ] check if the map is closed or not
- [ ] check for coma in wrong places inside `rgb`
- [ ] check for empty spaces inside the map (like multible lines)
- [ ] correct with `to_fix.cub` and `to_fix2.cub` so both throw an error.
