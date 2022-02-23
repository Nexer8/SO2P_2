# The Hairdresser's

A *C++* multithreaded program graphically representing, with the help of the *ncurses* library, a working day in a hairdressing salon. It uses *std::thread*.

![Simulation](images/simulation.gif)

## Assumptions

- Each Hairdresser needs two pairs of scissors: thinning scissors and hear cutting shears.
- The number of pairs of Scissors is exactly the same as the Hairdressers.
- Each hairdresser can only have one client assigned to him at a time.
- Customers are assigned to the Hairdresser in the order in which they are created (this is similar to the waiting room, the first to come will be served first).
- There can be multiple competing salons at one time.
- During the operation of the system, new scissors are brought from the store.

### Possible Hairdresser's States

- Waiting for a client
- Taking a break
- Cutting hair
- Waiting for scissors
- End of work

### Possible Customer's States

- Waiting for a cut
- Having a haircut
- Done
