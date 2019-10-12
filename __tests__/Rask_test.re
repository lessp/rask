open Jest;
open Expect;
open ReactTestingLibrary;

module Hello = {
  open Rask;

  [@react.component]
  let make = () =>
    Text.(
      make("Hello World!")
      ->fontFamily("Roboto")
      ->fontSize(32)
      ->color(Color.Red)
      ->toReactElement
    );
};

describe("Rask", () => {
  afterEach(cleanup);

  test("renders", () =>
    <Hello /> |> render |> container |> expect |> toMatchSnapshot
  );
});