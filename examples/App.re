open Rask;

module Container = {
  [@react.component]
  let make = (~children as c) => {
    View.(
      make("div")
      ->backgroundColor(Hex("7cc0c0"))
      ->display(Flex)
      ->flexDirection(Column)
      ->justifyContent(Center)
      ->alignItems(Center)
      ->height(Vh(100))
      ->width(Vw(100))
      ->children(c)
      ->toReactElement
    );
  };
};

module Hello = {
  [@react.component]
  let make = () => {
    let (currentText, setText) = React.useState(() => "Hello!");

    let toggleGreeting = _ =>
      setText(
        fun
        | "Hello!" => "World!"
        | _ => "Hello!",
      );

    let clickMe =
      Text.(
        make("Click the text below!")
        ->fontSize(18)
        ->color(DarkGrey)
        ->toReactElement
      );

    let helloWorld =
      Text.(
        make(currentText)
        ->fontFamily("sans-serif")
        ->fontSize(32)
        ->color(Hex("7cc0c0"))
        ->onClick(toggleGreeting)
        ->toReactElement
      );

    View.(
      make("div")
      ->backgroundColor(White)
      ->display(Flex)
      ->alignItems(Center)
      ->flexDirection(Column)
      ->justifyContent(Center)
      ->height(Px(320))
      ->width(Px(320))
      ->padding(~x=Px(32), ~y=Px(32))
      ->shadow(~x=0, ~y=14, ~blur=22, ~spread=-3, ~color=Rgba(0, 0, 0, 0.15))
      ->rounded(~all=5, ())
      ->children([|clickMe, helloWorld|]->React.array)
      ->toReactElement
    );
  };
};

[@react.component]
let make = () => <Container> <Hello /> </Container>;
