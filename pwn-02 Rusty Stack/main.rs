use libc;
use libc_stdhandle;

fn main() {
    unsafe {
        libc::setvbuf(libc_stdhandle::stdout(), &mut 0, libc::_IONBF, 0);

        libc::printf(format!("{}\n\0", r#"
██████╗  █████╗ ████████╗████████╗██╗     ███████╗   
██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║     ██╔════╝ 
██████╔╝███████║   ██║      ██║   ██║     █████╗ 
██╔══██╗██╔══██║   ██║      ██║   ██║     ██╔══╝   
██████╔╝██║  ██║   ██║      ██║   ███████╗███████╗ 
╚═════╝ ╚═╝  ╚═╝   ╚═╝      ╚═╝   ╚══════╝╚══════╝  
                                                  
 ██████╗ ███████╗ 
██╔═══██╗██╔════╝ 
██║   ██║█████╗ 
██║   ██║██╔══╝ 
╚██████╔╝██║ 
 ╚═════╝ ╚═╝  

██╗  ██╗ █████╗  ██████╗██╗  ██╗███████╗██████╗ ███████╗
██║  ██║██╔══██╗██╔════╝██║ ██╔╝██╔════╝██╔══██╗██╔════╝
███████║███████║██║     █████╔╝ █████╗  ██████╔╝███████╗
██╔══██║██╔══██║██║     ██╔═██╗ ██╔══╝  ██╔══██╗╚════██║
██║  ██║██║  ██║╚██████╗██║  ██╗███████╗██║  ██║███████║
╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝

██████╗  ██████╗ ██████╗ ██████╗ 
╚════██╗██╔═████╗╚════██╗╚════██╗ 
 █████╔╝██║██╔██║ █████╔╝ █████╔╝
██╔═══╝ ████╔╝██║██╔═══╝ ██╔═══╝ 
██╔═══╝ ████╔╝██║██╔═══╝ ██╔═══╝ 
███████╗╚██████╔╝███████╗███████╗ 
╚══════╝ ╚═════╝ ╚══════╝╚══════╝"#).as_ptr() as *const libc::c_char);

        libc::printf("I heard that Galvanization helps to protect metal from corrosion!\n\n\0".as_ptr() as *const libc::c_char);
        libc::printf("Do you have Tinker's tool to repair the Rusty Stack?\n> \0".as_ptr() as *const libc::c_char);

        let user_input = [0 as libc::c_char; 64].as_mut_ptr();
        libc::fgets(user_input, 64, libc_stdhandle::stdin());
        libc::printf("Here are the list of tools: \0".as_ptr() as *const libc::c_char);
        libc::printf(user_input);

        libc::printf("\nWell then, do you have what it takes to revert the Rust?\n> \0".as_ptr() as *const libc::c_char);
        libc::fgets(user_input, 128, libc_stdhandle::stdin());
    }
}