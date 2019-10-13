open Rask;

module Card = {
  let card =
    View.(
      make()
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
    );

  [@react.component]
  let make = (~children as c) => {
    View.(card->children(c)->reactElement("article"));
  };
};

module Title = {
  let title =
    Text.(
      make("")
      ->fontFamily("sans-serif")
      ->fontSize(32)
      ->color(Hex("7cc0c0"))
    );

  [@react.component]
  let make = (~text, ~onClick as handleClick) => {
    Text.(title->value(text)->onClick(handleClick)->reactElement);
  };
};
