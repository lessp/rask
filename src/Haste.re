module FontSize = {
  type t = int;

  let make = size => size;

  let toString = fs => string_of_int(fs) ++ "px";
};

module Color = {
  type t =
    | Black
    | Linen
    | Pink
    | Red
    | White
    | Rgba(int, int, int, float);

  let toString =
    fun
    | Black => "black"
    | Linen => "linen"
    | Pink => "pink"
    | Red => "red"
    | White => "white"
    | Rgba(r, g, b, a) =>
      "rgba("
      ++ [r, g, b]->Belt.List.map(string_of_int)->String.concat(", ", _)
      ++ ", "
      ++ Js.Float.toString(a)
      ++ ")";
};

module Size = {
  type t =
    | PCT(int)
    | PX(int)
    | VH(int)
    | VW(int);

  let parse =
    fun
    | PCT(x) => string_of_int(x) ++ "%"
    | PX(x) => string_of_int(x) ++ "px"
    | VH(x) => string_of_int(x) ++ "vh"
    | VW(x) => string_of_int(x) ++ "vw";
};

module BoxSizing = {
  type t =
    | BorderBox
    | ContentBox;

  let parse =
    fun
    | BorderBox => "border-box"
    | ContentBox => "content-box";
};

module Padding = {
  type t = {
    x: Size.t,
    y: Size.t,
  };

  let make = (~x, ~y) => {x, y};
  let empty = {x: PX(0), y: PX(0)};
  let parse = ({x, y}) => Size.parse(x) ++ " " ++ Size.parse(y);
};

module Shadow = {
  type t = {
    x: int,
    y: int,
    blur: int,
    spread: int,
    color: Color.t,
  };

  let make = (~x, ~y, ~blur, ~spread, ~color) => {x, y, blur, spread, color};
  let empty = {
    x: 0,
    y: 0,
    blur: 0,
    spread: 0,
    color: Color.Rgba(0, 0, 0, 0.1),
  };
  let toString = ({x, y, blur, spread, color}) =>
    [x, y, blur, spread]
    ->Belt.List.map(string_of_int)
    ->String.concat("px ", _)
    ++ "px "
    ++ color->Color.toString;
};

module View = {
  type t = {
    backgroundColor: Color.t,
    boxSizing: BoxSizing.t,
    shadow: Shadow.t,
    children: ReasonReact.reactElement,
    color: Color.t,
    elementType: string,
    fontFamily: string,
    fontSize: FontSize.t,
    height: Size.t,
    onChange: ReactEvent.Form.t => unit,
    onClick: ReactEvent.Mouse.t => unit,
    padding: Padding.t,
    width: Size.t,
  };

  /* default values */
  let empty = {
    backgroundColor: Color.White,
    boxSizing: BoxSizing.BorderBox,
    children: React.null,
    color: Color.Black,
    elementType: "div",
    fontFamily: "inherit",
    fontSize: FontSize.make(16),
    height: Size.PCT(100),
    shadow: Shadow.empty,
    onChange: _ => (),
    onClick: _ => (),
    padding: Padding.empty,
    width: Size.PCT(100),
  };

  /* init */
  let create = elementType => {...empty, elementType};

  /* all modifier functions */
  let backgroundColor = (backgroundColor, element) => {
    ...element,
    backgroundColor,
  };
  let boxSizing = (boxSizing, element) => {...element, boxSizing};
  let children = (children, element) => {...element, children};
  let color = (color, element) => {...element, color};
  let fontFamily = (fontFamily, element) => {...element, fontFamily};
  let fontSize = (fontSize, element) => {...element, fontSize};
  let height = (height, element) => {...element, height};
  let onChange = (onChange, element) => {...element, onChange};
  let onClick = (onClick, element) => {...element, onClick};
  let padding = (~x, ~y, element) => {
    ...element,
    padding: Padding.make(~x, ~y),
  };
  let width = (width, element) => {...element, width};
  let shadow = (~x, ~y, ~blur, ~spread, ~color, element) => {
    ...element,
    shadow: Shadow.make(~x, ~y, ~blur, ~spread, ~color),
  };

  let toReactElement = element => {
    [@react.component]
    let make = () => {
      let {
        backgroundColor,
        boxSizing,
        color,
        children,
        fontSize,
        fontFamily,
        height,
        onChange,
        onClick,
        padding,
        width,
        shadow,
      } = element;

      let styles =
        ReactDOMRe.Style.make(
          ~color=color->Color.toString,
          ~backgroundColor=backgroundColor->Color.toString,
          ~boxSizing=boxSizing->BoxSizing.parse,
          ~boxShadow=shadow->Shadow.toString,
          ~height=height->Size.parse,
          ~width=width->Size.parse,
          ~padding=padding->Padding.parse,
          ~fontSize=fontSize->FontSize.toString,
          ~fontFamily,
          (),
        );
      <div onChange onClick style=styles> children </div>;
    };
    make();
  };
};

module Text = {
  type t = {
    text: string,
    color: Color.t,
    fontSize: FontSize.t,
    fontFamily: string,
    onChange: ReactEvent.Form.t => unit,
    onClick: ReactEvent.Mouse.t => unit,
  };

  /* default values */
  let empty = {
    color: Color.Black,
    fontFamily: "sans-serif",
    fontSize: FontSize.make(16),
    onChange: _ => (),
    onClick: _ => (),
    text: "",
  };

  /* init */
  let create = text => {...empty, text};

  /* all modifier functions */
  let color = (color, element) => {...element, color};
  let fontFamily = (fontFamily, element) => {...element, fontFamily};
  let fontSize = (fontSize, element) => {...element, fontSize};
  let onChange = (onChange, element) => {...element, onChange};
  let onClick = (onClick, element) => {...element, onClick};

  let toReactElement = element => {
    [@react.component]
    let make = () => {
      let {text, fontFamily, color, fontSize, onChange, onClick} = element;

      let styles =
        ReactDOMRe.Style.make(
          ~color=color->Color.toString,
          ~fontSize=fontSize->FontSize.toString,
          ~fontFamily,
          (),
        );
      <p onChange onClick style=styles> {React.string(text)} </p>;
    };
    make();
  };
};
