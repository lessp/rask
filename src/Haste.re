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
    | Rgba(int, int, int, float)
    | Hex(string);

  let toString =
    Tablecloth.(
      fun
      | Black => "black"
      | Linen => "linen"
      | Pink => "pink"
      | Red => "red"
      | White => "white"
      | Rgba(r, g, b, a) =>
        "rgba("
        ++ [r, g, b]->List.map(~f=string_of_int)->String.join(~sep=", ")
        ++ ", "
        ++ Js.Float.toString(a)
        ++ ")"
      | Hex(hex) => hex |> String.contains(~substring="#") ? hex : "#" ++ hex
    );
};

module Flex = {
  module FlexDirection = {
    type t =
      | Row
      | RowReverse
      | Column
      | ColumnReverse;

    let empty = Row;
    let toString =
      fun
      | Row => "row"
      | RowReverse => "row-reverse"
      | Column => "column"
      | ColumnReverse => "column-reverse";
  };

  module JustifyContent = {
    type t =
      | Center
      | End
      | SpaceAround
      | SpaceBetween
      | SpaceEvenly
      | Start;

    let empty = Start;
    let toString =
      fun
      | Center => "center"
      | End => "flex-end"
      | SpaceAround => "space-around"
      | SpaceBetween => "space-between"
      | SpaceEvenly => "space-evenly"
      | Start => "flex-start";
  };

  module AlignItems = {
    type t =
      | Center
      | End
      | Start;

    let empty = Start;
    let toString =
      fun
      | Center => "center"
      | End => "flex-end"
      | Start => "flex-start";
  };
};

module Display = {
  type t =
    | Flex
    | Block
    | InlineBlock;

  let empty = InlineBlock;
  let toString =
    fun
    | Flex => "flex"
    | Block => "block"
    | InlineBlock => "inline-block";
};

module Size = {
  type t =
    | Pct(int)
    | Px(int)
    | Vh(int)
    | Vw(int);

  let parse =
    fun
    | Pct(x) => string_of_int(x) ++ "%"
    | Px(x) => string_of_int(x) ++ "px"
    | Vh(x) => string_of_int(x) ++ "vh"
    | Vw(x) => string_of_int(x) ++ "vw";
};

module Rounded = {
  type t = {
    topLeft: int,
    topRight: int,
    bottomLeft: int,
    bottomRight: int,
  };

  let make = (~topLeft=0, ~topRight=0, ~bottomLeft=0, ~bottomRight=0, all) => {
    switch (all) {
    | Some(radius) => {
        topLeft: radius,
        topRight: radius,
        bottomLeft: radius,
        bottomRight: radius,
      }
    | _ => {topLeft, topRight, bottomLeft, bottomRight}
    };
  };

  let empty = {topLeft: 0, topRight: 0, bottomLeft: 0, bottomRight: 0};

  let toString = ({topLeft, topRight, bottomLeft, bottomRight}) => {
    let borderRadius =
      Tablecloth.(
        [topLeft, topRight, bottomRight, bottomLeft]
        |> List.map(~f=string_of_int)
        |> String.join(~sep="px ")
      );

    borderRadius ++ "px";
  };
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
  let empty = {x: Px(0), y: Px(0)};
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
    alignItems: Flex.AlignItems.t,
    backgroundColor: Color.t,
    boxSizing: BoxSizing.t,
    shadow: Shadow.t,
    children: ReasonReact.reactElement,
    color: Color.t,
    display: Display.t,
    elementType: string,
    flexDirection: Flex.FlexDirection.t,
    fontFamily: string,
    fontSize: FontSize.t,
    justifyContent: Flex.JustifyContent.t,
    height: Size.t,
    onChange: ReactEvent.Form.t => unit,
    onClick: ReactEvent.Mouse.t => unit,
    padding: Padding.t,
    rounded: Rounded.t,
    width: Size.t,
  };

  /* default values */
  let empty = {
    alignItems: Flex.AlignItems.empty,
    backgroundColor: Color.White,
    boxSizing: BoxSizing.BorderBox,
    children: React.null,
    color: Color.Black,
    display: Display.empty,
    elementType: "div",
    flexDirection: Flex.FlexDirection.empty,
    fontFamily: "inherit",
    fontSize: FontSize.make(16),
    justifyContent: Flex.JustifyContent.empty,
    height: Size.Pct(100),
    shadow: Shadow.empty,
    onChange: _ => (),
    onClick: _ => (),
    padding: Padding.empty,
    rounded: Rounded.empty,
    width: Size.Pct(100),
  };

  /* init */
  let make = elementType => {...empty, elementType};

  /* all modifier functions */
  let alignItems = (element, alignItems) => {...element, alignItems};
  let backgroundColor = (element, backgroundColor) => {
    ...element,
    backgroundColor,
  };
  let boxSizing = (element, boxSizing) => {...element, boxSizing};
  let children = (element, children) => {...element, children};
  let color = (element, color) => {...element, color};
  let display = (element, display) => {...element, display};
  let flexDirection = (element, flexDirection) => {
    ...element,
    flexDirection,
  };
  let fontFamily = (element, fontFamily) => {...element, fontFamily};
  let fontSize = (element, fontSize) => {...element, fontSize};
  let justifyContent = (element, justifyContent) => {
    ...element,
    justifyContent,
  };
  let height = (element, height) => {...element, height};
  let onChange = (element, onChange) => {...element, onChange};
  let onClick = (element, onClick) => {...element, onClick};
  let padding = (element, ~x, ~y) => {
    ...element,
    padding: Padding.make(~x, ~y),
  };
  let rounded =
      (
        element,
        ~topLeft=0,
        ~topRight=0,
        ~bottomLeft=0,
        ~bottomRight=0,
        ~all=?,
        (),
      ) => {
    ...element,
    rounded:
      Rounded.make(~topLeft, ~topRight, ~bottomLeft, ~bottomRight, all),
  };
  let width = (element, width) => {...element, width};
  let shadow = (element, ~x, ~y, ~blur, ~spread, ~color) => {
    ...element,
    shadow: Shadow.make(~x, ~y, ~blur, ~spread, ~color),
  };

  let toReactElement = element => {
    [@react.component]
    let make = () => {
      let {
        alignItems,
        backgroundColor,
        boxSizing,
        color,
        children,
        display,
        flexDirection,
        fontSize,
        fontFamily,
        justifyContent,
        height,
        onChange,
        onClick,
        padding,
        rounded,
        width,
        shadow,
      } = element;

      let styles =
        ReactDOMRe.Style.make(
          ~alignItems=alignItems->Flex.AlignItems.toString,
          ~backgroundColor=backgroundColor->Color.toString,
          ~borderRadius=rounded->Rounded.toString,
          ~boxShadow=shadow->Shadow.toString,
          ~boxSizing=boxSizing->BoxSizing.parse,
          ~color=color->Color.toString,
          ~display=display->Display.toString,
          ~flexDirection=flexDirection->Flex.FlexDirection.toString,
          ~fontFamily,
          ~fontSize=fontSize->FontSize.toString,
          ~justifyContent=justifyContent->Flex.JustifyContent.toString,
          ~height=height->Size.parse,
          ~padding=padding->Padding.parse,
          ~width=width->Size.parse,
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
  let make = text => {...empty, text};

  /* all modifier functions */
  let color = (element, color) => {...element, color};
  let fontFamily = (element, fontFamily) => {...element, fontFamily};
  let fontSize = (element, fontSize) => {...element, fontSize};
  let onChange = (element, onChange) => {...element, onChange};
  let onClick = (element, onClick) => {...element, onClick};

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
