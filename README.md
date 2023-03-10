# Cube3d

## TO_FIX

- ~~Invalid extention for a file leaks~~
- ~~Non existent file leaks~~
- ~~Segfault if the file has no map~~
- ~~Segfault with only Player character~~
  - ~~Set minimum map size to : 3 x 3~~

## Maps to fix

```text
111
1N1
111
```

~~Should throw an error, it segfaults~~

```text
111
1S1
1010
111
```

~~Should troughw an error, it runs normally~~
