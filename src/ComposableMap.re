[@bs.module "react-simple-maps"]
external composableMap: ReasonReact.reactClass = "ComposableMap";

type projectionConfig = {
    scale : int,
    rotation : list(int),
};

[@bs.deriving abstract]
type jsProps = {
    width : int,
    height : int,
    projectionConfig : projectionConfig,
};

let make = (~width : int, ~height : int, ~projectionConfig : projectionConfig, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=composableMap,
    ~props=jsProps(
        ~width,
        ~height,
        ~projectionConfig,
    ),
    children,
  );