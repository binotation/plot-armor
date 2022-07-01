//! # Respawn
//! Dumb process respawner for immediately respawning a process executing a binary when it ends.
//! Uses the clap crate for parsing CLI args.

extern crate nix;

use clap::Parser;
use std::fs::OpenOptions;
use std::os::unix::io::{FromRawFd, IntoRawFd};
use std::process::{Command, Stdio};

/// Provide a path to a binary to respawn with -b. Specify stdout/stderr redirects with -o and -e.
/// Provide CLI args to the binary with --bin-args.
#[derive(Parser)]
#[clap(author, version, about)]
struct Args {
    /// Path to binary
    #[clap(short, long, value_parser)]
    bin: String,

    /// Redirect binary stdout to outf
    #[clap(short, long, value_parser, default_value = "bin.out")]
    outf: String,

    /// Redirect binary stderr to errf
    #[clap(short, long, value_parser, default_value = "bin.err")]
    errf: String,

    /// CLI args for binary
    #[clap(long, value_parser, multiple_values = true)]
    bin_args: Vec<String>,
}

fn main() -> ! {
    let args = Args::parse();

    loop {
        let outf_fd = OpenOptions::new()
            .write(true)
            .append(true)
            .create(true)
            .open(&args.outf)
            .expect("outf does not exist")
            .into_raw_fd();
        let errf_fd = OpenOptions::new()
            .write(true)
            .append(true)
            .create(true)
            .open(&args.errf)
            .expect("errf does not exist")
            .into_raw_fd();

        let (outf, errf) = unsafe { (Stdio::from_raw_fd(outf_fd), Stdio::from_raw_fd(errf_fd)) };

        let mut child = Command::new(&args.bin)
            .stdout(outf)
            .stderr(errf)
            .args(&args.bin_args)
            .spawn()
            .expect("Failed to spawn child");
        let _ = child.wait().expect("Failed to wait on child");
    }
}
