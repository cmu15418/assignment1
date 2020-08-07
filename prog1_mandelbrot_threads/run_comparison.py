
import re
import shlex
import subprocess
import matplotlib.pyplot as plt


if __name__ == "__main__":
    num_views = 2
    max_threads = 32
    num_threads = list(range(1, max_threads + 1))
    
    speedups = []
    for v in range(1, num_views + 1):
        speedups.append([])
        for i in num_threads:
            # Run compiled cpp program
            command = "./mandelbrot -t {:d} -v {:d}".format(i, v)
            completed_process = subprocess.run(shlex.split(command), capture_output=True)

            # Parse the stdout to and find the speedup factor
            speedup_str = re.findall(r"\d*\.\d*x", str(completed_process.stdout)).pop(-1)
            speedups[-1].append(float(speedup_str[:-1]))

    # Plot the resulting speedups
    fig, ax = plt.subplots()
    
    ax.plot(num_threads, speedups[0], linestyle='--', marker='v', color='b', label="view_1")
    ax.plot(num_threads, speedups[1], linestyle='--', marker='^', color='r', label="view_2")
    ax.set_xlim([0, max_threads + 1])

    ax.set_title("Thread Based Speedup")
    ax.set_xlabel("# Threads")
    ax.set_ylabel("x Speed")
    ax.legend()
    ax.grid()
    
    plt.savefig("speedup_comparison.svg")
    plt.savefig("speedup_comparison.png")
    plt.show()