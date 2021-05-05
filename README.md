# Philosophers

A classic thread management problem.
## The problem

K philosophers seated around a circular table. There is one chopstick between each philosopher. A philosopher may eat if he can pickup the two chopsticks adjacent to him. If each philosopher does not eat in a specefic time he may die. The goal of this problem is to correctly manage all resources so no philosopher dies.

## Project specifications

Simple usage:

```bash
    ./philo_* <n_philos> <time_to_die> <time_to_eat> <time_to_sleep> [<n_rounds>]
```

There are three different variations from the original problem:

**Philo_one** 

- There is one chopstick between each philosopher.
- Each philosopher is coded as a single `thread` and `mutexes` should be used to managed shared resources.
  
**Philo_two** 

- All chopsticks are now in the center of the table.
- Each philosopher is still coded as a single `thread` and `semaphores` should be used to manage shared resources.

**Philo_three** 

- All chopsticks are still in the center of the table.
- Each philosopher is now coded as a single `process` and `semaphores` are still used to manage shared resources.

## Usage

Clone the project

```bash
    git clone https://github.com/vdedios/philosophers
```

Go to the project directory and choose a philo proble

```bash
    cd project-directory/philo_*
```

Compile source code

```bash
    make
```

Run philos with desired params

```bash
    ./philo_* 4 410 200 200 4
```
## Author
<table>
    <tr>
        <td>
          <img src="https://cdn.intra.42.fr/users/small_vde-dios.jpg" width=140px>
          </br>
          <a href="https://github.com/vdedios">@vdedios</a>
        </td>
    </tr>
</table>

## Support

If you find any issue I suggest that you open a PR with the fix 🙂
