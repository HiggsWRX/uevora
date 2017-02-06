let f1 x = x + 1;;
let f2 x = x * x;;
let f3 x = x mod 2 = 0;;

let rec apl n f a = match n with
    | 0 -> a
    | _ -> apl (n-1) f (f a);;

let apl1 f a = apl 1 f a;;
let apl2 f a = apl 2 f a;;

let rec filter f l = match l with
    | [] -> []
    | h::t -> if (f h) then h::(filter f t) else filter f t;;

let rec append la lb = match la with
    | h::t -> h::append t lb
    | [] -> lb;;

let rec mem x l = match l with
    | [] -> false
    | h::t -> if x = h then true else mem x t;;

let rec remove la lb = match lb with
    | h::t -> if mem h la then remove la t else h::remove la t;;

let rec intersec la lb = match la with
    | [] -> []
    | h::t -> if (mem h lb) then h::(intersec t lb) else intersec t lb;;