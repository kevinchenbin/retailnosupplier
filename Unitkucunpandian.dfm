object frmkucunpandian: Tfrmkucunpandian
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #23454#24211#30424#28857
  ClientHeight = 243
  ClientWidth = 264
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object DBGrid1: TDBGrid
    Left = 0
    Top = 0
    Width = 264
    Height = 243
    Align = alClient
    Ctl3D = False
    DataSource = ds
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 0
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clNavy
    TitleFont.Height = -12
    TitleFont.Name = #24494#36719#38597#40657
    TitleFont.Style = []
    OnDblClick = DBGrid1DblClick
    OnKeyPress = DBGrid1KeyPress
    Columns = <
      item
        Expanded = False
        FieldName = 'checkstocknum'
        Title.Alignment = taCenter
        Title.Caption = #30424#28857#21333#21495
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'stackname'
        Title.Alignment = taCenter
        Title.Caption = #24211#20301
        Width = 80
        Visible = True
      end>
  end
  object ds: TDataSource
    DataSet = query
    Left = 248
    Top = 80
  end
  object query: TADOQuery
    Parameters = <>
    Left = 328
    Top = 144
  end
end
