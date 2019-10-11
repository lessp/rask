open Haste;

module HelloHaste = {
  [@react.component]
  let make = () => {
    let (currentText, setText) = React.useState(() => "Hello!");

    let toggleGreeting = _ =>
      setText(
        fun
        | "Hello!" => "World!"
        | _ => "Hello!",
      );

    View.(
      create("div")
      |> backgroundColor(Color.Linen)
      |> padding(~x=Size.PX(32), ~y=Size.PX(32))
      |> width(Size.PX(320))
      |> height(Size.PX(164))
      |> shadow(
           ~x=2,
           ~y=0,
           ~blur=12,
           ~spread=6,
           ~color=Color.Rgba(0, 0, 0, 0.1),
         )
      |> children(
           Text.(
             create(currentText)
             |> fontFamily("sans-serif")
             |> fontSize(32)
             |> color(Color.Pink)
             |> onClick(toggleGreeting)
             |> toReactElement
           ),
         )
      |> toReactElement
    );
  };
};

[@react.component]
let make = () => <HelloHaste />;
