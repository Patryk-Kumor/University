class OrdersController < ApplicationController
  before_action :authenticate_user!

  def index
    @orders = current_user.orders
  end

  def show
    @order = attach_order
  end

  private

  def attach_order
    order = current_user.orders.find_by(id: params[:id])
    return order if order

    order = current_guest.orders.find_by(id: params[:id])
    raise ActiveRecord::RecordNotFound unless order

    order.update owner: current_user

    order
  end
end
