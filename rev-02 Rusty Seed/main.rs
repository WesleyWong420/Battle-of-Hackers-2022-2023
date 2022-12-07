use libc::{uint64_t, c_double, c_char, c_int, _IONBF, setvbuf, strcspn, strcmp, printf, fgets, sscanf};
use libc_stdhandle;
use libsodium_sys;
use lazy_static::lazy_static;
use std::sync::Mutex;
use std::fs::File;
use std::io::BufReader;
use std::io::prelude::*;
use std::process;
use round::round;
use num_traits::pow;

lazy_static! {
    static ref SEED: Mutex<uint64_t> = Mutex::new(0);
}

fn init_seed(){
    unsafe{
        let rand1:uint64_t = libsodium_sys::randombytes_random() as uint64_t;
        let rand2:uint64_t = libsodium_sys::randombytes_random() as uint64_t;
        *SEED.lock().unwrap() = (rand1 << 32) + rand2;
    }
}

fn transform(start: c_double, end: c_double) -> uint64_t {

    let front:uint64_t = round(pow(10.0, end as usize), 1) as uint64_t;
    let end:uint64_t = round(pow(10.0, start as usize), 1) as uint64_t;
    let stripped:uint64_t = ((*SEED.lock().unwrap() % front) / end) as uint64_t;

    return stripped
}

fn stage1() -> uint64_t {
    let mut number:uint64_t = transform(4 as c_double, 12 as c_double);
    number *= number;
    return number
}

fn stage2() -> uint64_t {
    let number:uint64_t = transform(12 as c_double, 16 as c_double);
    return number
}

fn flag1() -> std::io::Result<()> {
    let file = File::open("flag1.txt")?;
    let mut buf_reader = BufReader::new(file);
    let mut contents = String::new();
    buf_reader.read_to_string(&mut contents)?;
    println!("{}", contents);
    Ok(())
}

fn flag2() -> std::io::Result<()> {
    let file = File::open("flag2.txt")?;
    let mut buf_reader = BufReader::new(file);
    let mut contents = String::new();
    buf_reader.read_to_string(&mut contents)?;
    println!("{}", contents);
    Ok(())
}

fn main(){
    unsafe {
        setvbuf(libc_stdhandle::stdout(), &mut 0, _IONBF, 0);
        let mut user_input = [0 as libc::c_char; 64];

        init_seed();

        loop  // Stage 1
        {
            println!("🌱 Rusty Seed - Stage 1:");
            println!("[1] Generate Random Number");
            println!("[2] Guess 2 Numbers");
            printf("> \0".as_ptr() as *const c_char);

            fgets(user_input.as_mut_ptr(), 64, libc_stdhandle::stdin());
            user_input[strcspn(user_input.as_mut_ptr(), b"\n\x00" as *const u8 as *const c_char) as usize] = 0 as c_int as c_char;

            if strcmp(b"1\x00" as *const u8 as *const c_char, user_input.as_mut_ptr()) == 0 {
                let randomNum:uint64_t = stage1();
                *SEED.lock().unwrap() = randomNum;
                println!("Output: {}", *SEED.lock().unwrap());
            }
            else if strcmp(b"2\x00" as *const u8 as *const c_char, user_input.as_mut_ptr()) == 0 {
                printf("[!] Guess the next two random numbers for a flag!\n[!] Enter your first guess:\n> \0".as_ptr() as *const c_char);
                
                let mut guess:uint64_t = 0 as uint64_t;
                fgets(user_input.as_mut_ptr(), 64, libc_stdhandle::stdin());
                sscanf(user_input.as_mut_ptr(), b"%lu\x00" as *const u8 as *const libc::c_char, &mut guess as *mut uint64_t);

                if guess == stage1(){
                    *SEED.lock().unwrap() = guess;
                    printf("✔️ Correct guess!\n\n\x1b[1;36mEnter your second guess:\n> \0".as_ptr() as *const c_char);
                }
                else {
                    printf("❌ Wrong answer! Try again!\n\0".as_ptr() as *const c_char);
                    continue;
                }

                guess = 0 as uint64_t;
                fgets(user_input.as_mut_ptr(), 64, libc_stdhandle::stdin());
                sscanf(user_input.as_mut_ptr(), b"%lu\x00" as *const u8 as *const libc::c_char, &mut guess as *mut uint64_t);

                if guess == stage1(){
                    *SEED.lock().unwrap() = guess;
                    printf("✔️ Correct guess!\n\n\x1b[1;37m🏳️ Here's the first portion of the flag: \0".as_ptr() as *const c_char);
                    flag1();
                    break;
                }
                else {
                    printf("❌ Not this time! Close enough!\n\0".as_ptr() as *const c_char);
                    continue;
                }
            }
        }

        init_seed();

        loop {  // Stage 2
            println!("🌱 Rusty Seed - Stage 2:\n");
            println!("[1] Generate Random Number");
            println!("[2] Guess 4 Numbers");
            printf("> \0".as_ptr() as *const c_char);

            fgets(user_input.as_mut_ptr(), 64, libc_stdhandle::stdin());
            user_input[strcspn(user_input.as_mut_ptr(), b"\n\x00" as *const u8 as *const c_char) as usize] = 0 as c_int as c_char;

            if strcmp(b"1\x00" as *const u8 as *const c_char, user_input.as_mut_ptr()) == 0 {
                let randomNum1:uint64_t = stage1();
                *SEED.lock().unwrap() = randomNum1;
                let randomNum2:uint64_t = stage2();
                println!("Output: {}", randomNum2);
            }
            else if strcmp(b"2\x00" as *const u8 as *const c_char, user_input.as_mut_ptr()) == 0 {
                printf("\n[!] Guess the next four random numbers for a flag!\n[!] Enter your first guess:\n> \0".as_ptr() as *const c_char);

                let mut x = 0;

                while x < 4 {
                    let mut guess:uint64_t = 0 as uint64_t;
                    fgets(user_input.as_mut_ptr(), 64, libc_stdhandle::stdin());
                    sscanf(user_input.as_mut_ptr(), b"%lu\x00" as *const u8 as *const libc::c_char, &mut guess as *mut uint64_t);

                    let randomNum1:uint64_t = stage1();
                    *SEED.lock().unwrap() = randomNum1;
                    let randomNum2:uint64_t = stage2();

                    if guess == randomNum2{
                        if x == 3 {
                            printf("✔️ Correct Guess No. 4!\n\n\x1b[1;37m🏳️ Here's your second half flag: \0".as_ptr() as *const c_char);
                            flag2();
                            process::exit(1);
                        }
                        else{
                            printf("✔️ Correct Guess No. %d!\n\n\x1b[1;93mEnter your next guess:\n> \0".as_ptr() as *const c_char, x+1);
                            x += 1;
                        }
                    }
                    else {
                        printf("\n\x1b[1;31m❌ Wrong answer! Try again!\0".as_ptr() as *const c_char);
                        break;
                    }
                }
            }
        }
    }
}
